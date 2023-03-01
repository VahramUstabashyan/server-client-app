#include "ClientCommandHandler.hpp"

ClientCommandHandler::ClientCommandHandler(std::unique_ptr<Client> client)
    : client(std::move(client)) {
}

bool ClientCommandHandler::handle_command(const std::string& command) {
    std::istringstream command_ss(command);
    std::string token;
    std::getline(command_ss, token, ' ');
    if (token == "connect") {
        /// Handle connect
        std::cout << "connecting..." << std::endl;
    } else if (token == "disconnect") {
        /// Handle disconnect
        std::cout << "disconnecting..." << std::endl;
    } else if (token == "shell") {
        /// Handle shell command
        std::cout << "executing shell command..." << std::endl;
    } else if (token == "quit") {
        /// Handle quit
        return true;
    } else {
        std::cerr << "Unknown command: " << token << std::endl;
    }
    return false;
}
