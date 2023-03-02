#include "Connection.hpp"

Connection::Connection(std::unique_ptr<tcp::socket> socket_ptr)
        : socket_ptr(std::move(socket_ptr)),
          read_buf(512) {

}

void Connection::read() {
    boost::asio::async_read_until(
            *socket_ptr, read_buf, '\n',
            [this](boost::system::error_code err, std::size_t bytes_read) {
                handle_read(err, bytes_read);
            }
    );
}

void Connection::handle_read(boost::system::error_code err, std::size_t bytes_read) {
    if (err) std::cout << "Error code: " << err << std::endl;
    read_msg = {boost::asio::buffers_begin(read_buf.data()), boost::asio::buffers_end(read_buf.data())};
    std::cout << "Received message: " << read_msg << std::endl;
    read_buf.consume(bytes_read);
    read();
}

void Connection::writeln(const std::string& msg) {
    write(msg + '\n');
}

void Connection::write(const std::string& msg) {
    socket_ptr->async_send(boost::asio::buffer(msg),
                           [this](boost::system::error_code e, std::size_t bytes_written) {
                               handle_write(e, bytes_written);
                           });
}

void Connection::handle_write(boost::system::error_code err, std::size_t bytes_written) {
    if (err) {
        std::cout << "Writing to " << remote_ip_port() << " failed with error code: " << err << std::endl;
        return;
    }
    std::cout << "Written " << bytes_written << " bytes to " << remote_ip_port() << std::endl;
}

std::string Connection::remote_ip_port() {
    return socket_ptr->remote_endpoint().address().to_string()
           + ":" + std::to_string(socket_ptr->remote_endpoint().port());
}

void Connection::close() {
    socket_ptr->close();
}
