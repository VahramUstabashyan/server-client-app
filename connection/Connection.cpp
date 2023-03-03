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
    if (bytes_read) {
        read_msg = {boost::asio::buffers_begin(read_buf.data()), boost::asio::buffers_end(read_buf.data())};
        std::cout << "Received message (" << bytes_read << " bytes): " << read_msg << std::endl;
        read_buf.consume(bytes_read);
        update();
    }
    read();
}

std::string Connection::get_last_msg() const {
    return read_msg;
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

void Connection::handle_write(boost::system::error_code err, std::size_t bytes_written) const {
    if (err) {
        std::cout << "Writing to " << remote_ip_port() << " failed with error code: " << err << std::endl;
        return;
    }
    std::cout << "Written " << bytes_written << " bytes to " << remote_ip_port() << std::endl;
}

std::string Connection::remote_ip_port() const {
    return socket_ptr->remote_endpoint().address().to_string()
           + ":" + std::to_string(socket_ptr->remote_endpoint().port());
}

void Connection::close() {
    socket_ptr->close();
}

void Connection::update() {
    std::cout << "New message from " << remote_ip_port() << std::endl;
    auto response = observer->handle_new_message(get_last_msg());
    if (!response.empty()) writeln(response);
}
