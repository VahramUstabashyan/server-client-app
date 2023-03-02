#pragma once

#include <string>
#include <boost/asio.hpp>

#include "../connection/Connection.hpp"


class Client {
private:
    /// TCP connection context and thread
    boost::asio::io_context io_context;
    std::thread io_thread;

    /// Connection with server
    std::shared_ptr<Connection> server;
public:
    /// Constructor
    Client();

    /**
     * Construct and connect
     * @param ip IP address of the server
     * @param port Connection port
     */
    Client(const std::string& ip, int port);

    /// Destructor
    ~Client();

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
    std::string shell(std::string command);

private:
    /**
     * Handle connection request
     * @param err Error code
     * @param socket_ptr TCP socket pointer
     */
    void handle_connect(boost::system::error_code err, std::unique_ptr<tcp::socket> socket_ptr);
};
