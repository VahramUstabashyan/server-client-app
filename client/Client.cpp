#include "Client.hpp"

void Client::connect(const std::string& ip, int port) {
    try {
        auto endpoint = tcp::endpoint(boost::asio::ip::make_address(ip), port);
        auto socket_ptr = std::make_unique<tcp::socket>(io_service, endpoint.protocol());
        socket_ptr->connect(endpoint);
        server = std::make_shared<Connection>(std::move(socket_ptr));
        server->set_observer(shared_from_this());
        server->read();
        std::cout << "Connection successfully established with " << server->remote_ip_port() << std::endl;
    } catch (boost::system::system_error &e) {
        std::cout << "Error occurred while connecting: " << e.what() << std::endl;
    }
}

void Client::shell(const std::string& command) {
    if (!server) return not_connected();
    server->writeln(command);
}

std::string Client::handle_new_message(std::string msg) {
    std::cout << "Received message: " << msg << std::endl;
    return {};
}
