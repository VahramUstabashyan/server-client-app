#include "ClientCommandHandler.hpp"

ClientCommandHandler::ClientCommandHandler(std::shared_ptr<Client> client)
        : client(std::move(client)) {
}

bool ClientCommandHandler::handle_command(const std::string& command) {
    try {
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
            client->disconnect();
        } else if (token == "shell") {
            /// Handle shell command
            std::string cmd;
            cmd = get_in_quotes(command_ss);
            std::cout << "executing shell command... Command: " << cmd << std::endl;
            client->shell(cmd);
        } else if (token == "quit") {
            /// Handle quit
            return true;
        } else {
            std::cerr << "Unknown command: " << token << std::endl;
        }
    } catch (std::invalid_argument& e) {
        std::cerr << "Error while processing command: " << e.what() << std::endl;
    }
    return false;
}

std::string ClientCommandHandler::get_argument(std::istringstream& ss) {
    std::string token;
    std::getline(ss, token, ' ');
    if (token.empty()) {
        throw std::invalid_argument("Argument missing");
    }
    return token;
}

std::string ClientCommandHandler::get_in_quotes(std::istringstream& ss) {
    std::string token;
    std::getline(ss, token, '"');
    std::getline(ss, token, '"');
    if (token.empty()) {
        throw std::invalid_argument("Argument missing");
    } else if (ss.str().back() != '"') {
        throw std::invalid_argument("Missing quote(s)");
    }
    return token;
}
