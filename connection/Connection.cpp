#include "Connection.hpp"

Connection::Connection(std::unique_ptr<tcp::socket> socket_ptr)
        : socket_ptr(std::move(socket_ptr)),
          read_buf(512) {

}

void Connection::read() {
    if (!is_open()) return;
    boost::asio::async_read_until(
            *socket_ptr, read_buf, END_OF_MESSAGE,
            [this](boost::system::error_code err, std::size_t bytes_read) {
                handle_read(err, bytes_read);
            }
    );
}

void Connection::handle_read(boost::system::error_code err, std::size_t bytes_read) {
    if (!is_open()) return;
    if (err) {
        std::cout << "Error code: " << err << std::endl;
        close();
        std::cout << "Disconnected" << std::endl;
        return;
    }
    if (bytes_read) {
        read_msg = {boost::asio::buffers_begin(read_buf.data()), boost::asio::buffers_end(read_buf.data())};
//        std::cout << "Received message (" << bytes_read << " bytes): " << read_msg << std::endl;
        read_buf.consume(read_buf.size());
        update();
    }
    read();
}

std::string Connection::get_last_msg() const {
    return read_msg;
}

void Connection::writeln(const std::string& msg) {
    write(msg + END_OF_MESSAGE);
}

void Connection::write(const std::string& msg) {
    if (!is_open()) return;
    socket_ptr->async_send(boost::asio::buffer(msg),
                           [this](boost::system::error_code e, std::size_t bytes_written) {
                               handle_write(e, bytes_written);
                           });
}

void Connection::handle_write(boost::system::error_code err, std::size_t bytes_written) const {
    if (err) {
        return; 
    }
//    std::cout << "Written " << bytes_written << " bytes to " << remote_ip_port() << std::endl;
}

std::string Connection::remote_ip_port() const {
    return socket_ptr->remote_endpoint().address().to_string()
           + ":" + std::to_string(socket_ptr->remote_endpoint().port());
}

bool Connection::is_open() {
    return socket_ptr && socket_ptr->is_open();
}

void Connection::close() {
    if (socket_ptr) socket_ptr->close();
    socket_ptr = nullptr;
}

void Connection::update() {
//    std::cout << "New message from " << remote_ip_port() << std::endl;
    auto observer = observer_weak.lock();
    if (!observer) return;
    auto msg = get_last_msg();
    size_t pos;
    while ((pos = msg.find(END_OF_MESSAGE)) != std::string::npos) msg.erase(pos, END_OF_MESSAGE.length());
    observer->handle_new_message(msg, remote_ip_port());
}
