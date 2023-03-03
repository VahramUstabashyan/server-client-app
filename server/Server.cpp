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

        auto client = std::make_unique<Connection>(std::make_unique<tcp::socket>(std::move(socket)));
        if (num_clients < max_clients) {
            auto remote_ip_port = client->remote_ip_port();
            client->set_observer(weak_from_this());
            client->read();
            clients[remote_ip_port] = std::move(client);
            ++num_clients;
            std::cout << "Client " << remote_ip_port << " successfully added!" << std::endl;
        } else {
            std::cout << "Failed to add client: maximum number of clients reached (" << max_clients << ")" << std::endl;
            client->writeln("Maximum number of clients reached. Connection rejected.");
            client->close();
        }
    }
    async_accept();
}

std::string Server::handle_new_message(std::string msg, const std::string& ip_port) {
    if (msg == "disconnect") {
        disconnect(ip_port);
        std::cout << "Successfully disconnected from client " << ip_port << std::endl;
        return {};
    } else {
        return shell(msg);
    }
}

void Server::disconnect(const std::string& ip_port) {
    clients[ip_port]->close();
    clients.erase(ip_port);
    --num_clients;
}

std::string Server::shell(const std::string& command) {
    std::array<char, 128> buffer{};
    std::string output;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(
            popen((command + " 2>&1").c_str(), "r"),  // Redirect `stderr` to `stdout`
            pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        output += buffer.data();
    }
    return output;
}
