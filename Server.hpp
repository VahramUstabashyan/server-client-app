#pragma once

#include <string>


class Server {
public:
    /// Constructors
    Server();
    Server(std::string ip, int port);

    /**
     * Disconnect from the client
     * @return Success
     */
    bool disconnect();

    /**
     * Execute command in the shell
     * @param command Shell command to execute
     * @return Response message
     */
    std::string shell(std::string command);
};
