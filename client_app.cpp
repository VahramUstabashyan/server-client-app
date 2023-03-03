#include <iostream>
#include <memory>

#include "client/Client.hpp"
#include "client/ClientCommandHandler.hpp"

int main() {
    std::cout << "This is client application." << std::endl;

    auto client = std::make_shared<Client>();
    auto command_handler = std::make_unique<ClientCommandHandler>(std::move(client));

    std::string user_input;
    bool quit = false;
    while (!quit) {
        std::getline(std::cin, user_input);
        quit = command_handler->handle_command(user_input);
    }
}
