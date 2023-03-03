#include "Client.hpp"

void Client::connect(const std::string& ip, int port) {
    if (server) return already_connected();
    try {
        auto endpoint = tcp::endpoint(boost::asio::ip::make_address(ip), port);
        auto socket_ptr = std::make_unique<tcp::socket>(io_context);
        socket_ptr->connect(endpoint);
        server = std::make_shared<Connection>(std::move(socket_ptr));
        server->set_observer(shared_from_this());
        server->read();
        io_thread = std::thread([this]() {
            io_context.run();
        });
        std::cout << "Connection successfully established with " << server->remote_ip_port() << std::endl;
    } catch (boost::system::system_error &e) {
        std::cerr << "Error occurred while connecting: " << e.what() << '\n';
    }
}

void Client::shell(const std::string& command) {
    if (!server) return not_connected();
    server->writeln(command);
}

std::string Client::handle_new_message(std::string msg) {
    std::cout << "Server response: " << msg << std::endl;
    return {};
}
