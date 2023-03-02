#include "ClientCommandHandler.hpp"

ClientCommandHandler::ClientCommandHandler(std::unique_ptr<Client> client)
        : client(std::move(client)) {
}

bool ClientCommandHandler::handle_command(const std::string& command) {
    std::istringstream command_ss(command);
    std::string token = get_argument(command_ss);
    if (token == "connect") {
        /// Handle connect
        std::string ip = get_argument(command_ss);
        int port = std::stoi(get_argument(command_ss));
        std::cout << "connecting to server with IP: " << ip
                  << " on port: " << port << std::endl;
        client->connect(ip, port);
    } else if (token == "disconnect") {
        /// Handle disconnect
        std::cout << "disconnecting..." << std::endl;
//        client->disconnect();
    } else if (token == "shell") {
        /// Handle shell command
        std::string cmd = get_argument(command_ss);
        std::cout << "executing shell command... Command: " << cmd << std::endl;
        client->shell(cmd);
    } else if (token == "quit") {
        /// Handle quit
        return true;
    } else {
        std::cerr << "Unknown command: " << token << std::endl;
    }
    return false;
}

std::string ClientCommandHandler::get_argument(std::istringstream& ss) {
    std::string token;
    std::getline(ss, token, ' ');
    if (token.empty()) {
        std::cout << "Argument missing." << std::endl;
    }
    return token;
}
