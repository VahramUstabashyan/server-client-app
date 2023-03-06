#include <iostream>

#include "server/Server.hpp"
#include "client/Client.hpp"
#include "client/ClientCommandHandler.hpp"

using namespace std::chrono_literals;


void test_command(std::unique_ptr<ClientCommandHandler>& cmd_handler, const std::string& cmd) {
    cmd_handler->handle_command(cmd);
    std::this_thread::sleep_for(2s);
}


int main() {
    std::cout << "This is test executable. It will end automatically." << std::endl;

    auto server = std::make_shared<Server>("0.0.0.0", 55555);
    auto client = std::make_shared<Client>();
    auto command_handler = std::make_unique<ClientCommandHandler>(std::move(client));

    test_command(command_handler, "connect 127.0.0.1 55555");
    test_command(command_handler, "shell \"pwd\"");
    test_command(command_handler, "shell \"ping 1.1.1.1 -c 1\"");
    test_command(command_handler, "shell \"date\"");
    test_command(command_handler, "disconnect");
    test_command(command_handler, "connect 127.0.0.1 55555");
    test_command(command_handler, "disconnect");
}