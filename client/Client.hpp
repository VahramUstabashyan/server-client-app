#pragma once

#include <string>


class Client {
public:
    /// Constructors
    Client();
    Client(std::string ip, int port);

    /**
     * Connect to the server by IP and Port
     * @param ip IP address of the server
     * @param port Connection port
     * @return Success
     */
    bool connect(std::string ip, int port);

    /**
     * Disconnect from the server
     * @return Success
     */
     bool disconnect();

     /**
      * Send shell command to the server
      * @param command Shell command to execute on server
      * @return Response message
      */
     std::string shell(std::string command);
};
