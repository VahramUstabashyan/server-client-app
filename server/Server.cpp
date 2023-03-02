#include "Server.hpp"

Server::Server(const std::string& ip, int port)
        : acceptor(io_context,
                   tcp::endpoint(boost::asio::ip::make_address(ip), port)) {
    for (int i = 0; i < max_clients; ++i) {
        clients.push_back(nullptr);
    }
    async_accept();
    io_thread = std::thread([this]() {
        io_context.run();
    });
}

Server::~Server() {
    if (io_thread.joinable()) {
        io_context.stop();
        io_thread.join();
    }
}

void Server::async_accept() {
    acceptor.async_accept([this](boost::system::error_code err,
                                 tcp::socket socket) {
        handle_connection(err, socket);
    });
}

void Server::handle_connection(boost::system::error_code err,
                               tcp::socket& socket) {
    if (!err) {
        std::cout << "Connection request" << std::endl;

        bool success = false;
        for (auto& connection_p : clients) {
            if (!connection_p) {
                connection_p = std::make_shared<Connection>(
                        std::make_unique<tcp::socket>(std::move(socket)));
                connection_p->read();
                success = true;
                std::cout << "Client " << connection_p->remote_ip_port() << " successfully added!" << std::endl;
                break;
            }
        }
        if (!success) {
            std::cout << "Failed to add client: maximum number of clients reached (" << max_clients << ")" << std::endl;
        }
    }
    async_accept();
}
