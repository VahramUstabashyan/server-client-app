#include "Connection.hpp"

Connection::Connection(std::shared_ptr<tcp::socket> socket_ptr)
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

std::string Connection::remote_ip_port() {
    return socket_ptr->remote_endpoint().address().to_string()
           + ":" + std::to_string(socket_ptr->remote_endpoint().port());
}
