#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include "../client/Client.hpp"

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

private:
    static std::string get_argument(std::istringstream& ss);
};
