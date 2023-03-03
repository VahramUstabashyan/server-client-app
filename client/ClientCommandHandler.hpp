#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include "Client.hpp"

class ClientCommandHandler {
private:
    /// Client to handle commands for
    std::shared_ptr<Client> client;
public:
    /// Constructor
    explicit ClientCommandHandler(std::shared_ptr<Client> client);

    /**
     * Handle user command for client
     * @param command User input command
     * @return Quit (whether the command is "quit")
     */
    bool handle_command(const std::string& command);

private:
    /**
     * Get next argument from user input
     * @param ss Input sstream
     * @return Argument
     */
    static std::string get_argument(std::istringstream& ss);

    /**
     * Get value in quotes
     * @param ss Input sstream
     * @return Value in quotes
     */
    static std::string get_in_quotes(std::istringstream& ss);
};
