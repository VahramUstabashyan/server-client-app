#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <unordered_map>

#include "Client.hpp"

class ClientCommandHandler {
private:
    /// Client to handle commands for
    std::shared_ptr<Client> client;

    /// Available commands map
    typedef void (ClientCommandHandler::*command_method_t)(std::istringstream&);
    const std::unordered_map<std::string, command_method_t> commands = {
            {"quit", &ClientCommandHandler::quit},
            {"help", &ClientCommandHandler::help},
            {"shell", &ClientCommandHandler::shell},
            {"disconnect", &ClientCommandHandler::disconnect},
            {"connect", &ClientCommandHandler::connect}
    };
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

    /**
     * Check if no more arguments left and throw otherwise
     * @param ss Input sstream
     */
    static void check_empty(std::istringstream& ss);

    /**
     * Connect to the server
     * @param ss Input sstream
     */
    void connect(std::istringstream& ss);

    /**
     * Disconnect from the server
     * @param ss Input sstream
     */
    void disconnect(std::istringstream& ss);

    /**
     * Run shell command on the server
     * @param ss Input sstream
     */
    void shell(std::istringstream& ss);

    /**
     * Show available command list
     * @param ss Input sstream
     */
    void help(std::istringstream& ss);

    /**
     * Quit the application
     * @param ss Input sstream
     */
    void quit(std::istringstream& ss);
};
