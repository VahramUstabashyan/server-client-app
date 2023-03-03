#include "Client.hpp"

Client::Client() {
    server = std::make_shared<Connection>();
}

void Client::connect(const std::string& ip, int port) {
    if (server->is_open()) return already_connected();
    try {
        auto endpoint = tcp::endpoint(boost::asio::ip::make_address(ip), port);
        auto socket_ptr = std::make_unique<tcp::socket>(io_context);
        socket_ptr->connect(endpoint);
        server = std::make_shared<Connection>(std::move(socket_ptr));
        server->set_observer(weak_from_this());
        server->read();
        io_thread = std::thread([this]() {
            io_context.run();
        });
        std::cout << "Connection successfully established with " << server->remote_ip_port() << std::endl;
    } catch (boost::system::system_error &e) {
        std::cerr << "Error occurred while connecting: " << e.what() << '\n';
    }
}

void Client::disconnect() {
    if (!server->is_open()) return not_connected();
    server->writeln("disconnect");
    server->close();
    io_context.stop();
    io_thread.join();
}

void Client::shell(const std::string& command) {
    if (!server->is_open()) return not_connected();
    server->writeln(command);
}

std::string Client::handle_new_message(std::string msg, const std::string& ip_port) {
    std::cerr << msg << std::endl;
    return {};
}

Client::~Client() {
    disconnect();
}
