#include "Client.hpp"

Client::Client() {}

Client::Client(const std::string& ip, int port) : Client() {
    connect(ip, port);
}

Client::~Client() {
    if (io_thread.joinable()) {
        io_context.stop();
        io_thread.join();
    }
}

void Client::connect(const std::string& ip, int port) {
    auto socket_ptr = std::make_unique<tcp::socket>(io_context);
    auto endpoints = tcp::resolver(io_context).resolve(ip, std::to_string(port));
    boost::asio::async_connect(*socket_ptr, endpoints,
                               [this, &socket_ptr](boost::system::error_code err, const tcp::endpoint& ep) {
                                   handle_connect(err, std::move(socket_ptr));
                               });
    io_thread = std::thread([this]() {
        io_context.run();
    });
}

void Client::handle_connect(boost::system::error_code err, std::unique_ptr<tcp::socket> socket_ptr) {
    server = std::make_shared<Connection>(std::move(socket_ptr));
    if (err) {
        std::cout << "Failed to connect to the server." << std::endl;
        return;
    }
    std::cout << "Connection successfully established with " << server->remote_ip_port() << std::endl;
}
