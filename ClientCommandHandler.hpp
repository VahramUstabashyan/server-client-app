#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "Client.hpp"

class ClientCommandHandler {
private:
    /// Client to handle commands for
    std::unique_ptr<Client> client;
public:
    /// Constructor
    explicit ClientCommandHandler(std::unique_ptr<Client> client);

    /**
     * Handle user command for client
     * @param command User input command
     * @return Quit (whether the command is "quit")
     */
    bool handle_command(const std::string& command);
};
