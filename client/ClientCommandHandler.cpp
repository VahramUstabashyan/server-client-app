#include "ClientCommandHandler.hpp"

ClientCommandHandler::ClientCommandHandler(std::shared_ptr<Client> client)
        : client(std::move(client)) {
}

bool ClientCommandHandler::handle_command(const std::string& command) {
    if (command.empty()) return false;

    std::istringstream command_ss(command);
    std::string token = get_argument(command_ss);

    if (token == "quit") {
        check_empty(command_ss);
        return true;
    }

    auto cmd = commands.find(token);
    if (cmd != commands.end()) {
        try {
            (this->*(cmd->second))(command_ss);
        } catch (std::invalid_argument& e) {
            std::cerr << "Error while processing command: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Unknown command: " << token << std::endl;
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

void ClientCommandHandler::check_empty(std::istringstream& ss) {
    std::string token;
    std::getline(ss, token, ' ');
    if (!token.empty()) {
        throw std::invalid_argument("Unknown argument: " + token);
    }
}

void ClientCommandHandler::connect(std::istringstream& ss) {
    std::string ip = get_argument(ss);
    int port = std::stoi(get_argument(ss));
    check_empty(ss);
    client->connect(ip, port);
}

void ClientCommandHandler::disconnect(std::istringstream& ss) {
    check_empty(ss);
    client->disconnect();
}

void ClientCommandHandler::shell(std::istringstream& ss) {
    std::string cmd;
    cmd = get_in_quotes(ss);
    check_empty(ss);
    client->shell(cmd);
}

void ClientCommandHandler::help(std::istringstream& ss) {
    check_empty(ss);
    std::cout << "Available commands:" << std::endl;
    for (auto cmd : commands) {
        std::cout << " - " << cmd.first << std::endl;
    }
}

void ClientCommandHandler::quit(std::istringstream& ss) {
    check_empty(ss);
}
