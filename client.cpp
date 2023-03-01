#include <iostream>
#include <memory>

#include "Client.hpp"
#include "ClientCommandHandler.hpp"

int main() {
    std::cout << "This is client application." << std::endl;

//    auto client = std::make_unique<Client>("1.2.3.4", 80);
    auto client = std::make_unique<Client>();
    auto command_handler = std::make_unique<ClientCommandHandler>(std::move(client));

    std::string user_input;
    bool exit = false;
    while (!exit) {
        std::getline(std::cin, user_input);
        exit = command_handler->handle_command(user_input);
    }
}
