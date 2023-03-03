#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <thread>
#include <boost/asio.hpp>

#include "../connection/Connection.hpp"

using boost::asio::ip::tcp;

class Server : public ConnectionObserver {
private:
    /// TCP connection context, acceptor and thread
    boost::asio::io_context io_context;
    tcp::acceptor acceptor;
    std::thread io_thread;

    /// Client connections vector
    std::map<std::string, std::unique_ptr<Connection>> clients;

    /// Maximum number of clients
    const int max_clients = 5;

    /// Number of connected clients
    std::atomic<int> num_clients;
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
    static std::string shell(const std::string& command);

    /**
     * Handle new message
     * @param msg Received message
     * @return Response
     */
    std::string handle_new_message(std::string msg) override;

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
    void handle_connection(boost::system::error_code err, tcp::socket socket);
};
