#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <thread>
#include <boost/asio.hpp>
#include <unistd.h>
#include <sys/wait.h>

#include "../connection/Connection.hpp"

using boost::asio::ip::tcp;

class Server : public ConnectionObserver {
private:
    /// TCP connection context, acceptor and thread
    boost::asio::io_context io_context;
    tcp::acceptor acceptor;
    std::thread io_thread;

    /// Client connections
    std::map<std::string, std::unique_ptr<Connection>> clients;

    /// PIDs and threads of processed run by clients
    std::map<std::string, std::vector<int>> pids;
    std::map<std::string, std::vector<std::thread>> p_threads;

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
     * @param ip_port Client IP and Port in ip:port format
     */
    void disconnect(const std::string& ip_port);

    /**
     * Execute command in the shell
     * @param command Shell command to execute
     * @param ip_port Client IP and Port in ip:port format
     */
    void shell(const std::string& command, const std::string& ip_port);

    /**
     * Handle new message
     * @param msg Received message
     * @param ip_port Client IP and Port in ip:port format
     */
    void handle_new_message(std::string msg, const std::string& ip_port) override;

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
