#pragma once

#include <string>
#include <boost/asio.hpp>

#include "../connection/Connection.hpp"


class Client {
private:
    /// TCP connection io service
    boost::asio::io_service io_service;

    /// Connection with server
    std::shared_ptr<Connection> server;
public:
    /// Default constructor
    Client() = default;

    /**
     * Construct and connect
     * @param ip IP address of the server
     * @param port Connection port
     */
    Client(const std::string& ip, int port);

    /**
     * Connect to the server by IP and Port
     * @param ip IP address of the server
     * @param port Connection port
     */
    void connect(const std::string& ip, int port);

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
    void shell(const std::string& command);
};
