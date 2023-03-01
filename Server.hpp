#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <boost/asio.hpp>

#include "Connection.hpp"

using boost::asio::ip::tcp;

class Server {
private:
    /// TCP connection context, acceptor and thread
    boost::asio::io_context io_context;
    tcp::acceptor acceptor;
    std::thread io_thread;

    /// Client connections vector
    std::vector<std::shared_ptr<Connection>> clients;

    /// Maximum number of clients
    const int max_clients = 5;
public:
    /// Constructor
    Server(const std::string& ip, int port);

    /// Destructor
    ~Server();

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

private:
    /**
     * Asynchronously wait for new clients
     */
    void async_accept();

    /**
     * Handle new client connection
     * @param socket TCP socket pointer
     * @param err Error code when trying to accept connection
     */
    void handle_connection(boost::system::error_code err, tcp::socket& socket);

};
