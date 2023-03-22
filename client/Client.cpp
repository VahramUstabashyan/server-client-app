#include "Client.hpp"

Client::Client() {
    server = std::make_shared<Connection>();
}

void Client::connect(const std::string& ip, int port) {
    std::cout << "Connecting to server with IP: " << ip
              << " on port: " << port << std::endl;
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
    std::cout << "Disconnecting from the server" << std::endl;
    if (!server->is_open()) return not_connected();
    auto server_ip_port = server->remote_ip_port();
    server->writeln("disconnect");
    server->close();
    io_context.stop();
    io_thread.join();
    server = std::make_shared<Connection>();
    std::cout << "Successfully disconnected from the server " << server_ip_port << std::endl;
}

void Client::shell(const std::string& command) {
    std::cout << "Executing shell command: " << command << std::endl;
    if (!server->is_open()) return not_connected();
    server->writeln(command);
}

void Client::handle_new_message(std::string msg, const std::string& ip_port) {
    std::cerr << msg << std::endl;
}

Client::~Client() {
    if (server->is_open()) disconnect();
}
