#include <iostream>
#include <memory>
#include <readline/readline.h>
#include <readline/history.h>

#include "client/Client.hpp"
#include "client/ClientCommandHandler.hpp"

int main() {
    std::cout << "This is client application." << std::endl;
    std::cout << "Enter 'quit' to stop." << std::endl;

    auto client = std::make_shared<Client>();
    auto command_handler = std::make_unique<ClientCommandHandler>(std::move(client));

    std::string user_input;
    bool quit = false;
    while (!quit) {
        user_input = readline("client$ ");
        if (user_input.length() > 0) add_history(user_input.c_str());
        quit = command_handler->handle_command(user_input);
    }
}
