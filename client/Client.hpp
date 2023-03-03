#pragma once

#include <memory>
#include <string>
#include <thread>
#include <boost/asio.hpp>

#include "../connection/Connection.hpp"
#include "../observer/ConnectionObserver.hpp"


class Client : public ConnectionObserver {
private:
    /// TCP connection context and thread
    boost::asio::io_context io_context;
    std::thread io_thread;

    /// Connection with server
    std::shared_ptr<Connection> server;
public:
    /// Default constructor
    Client();

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
     */
    void disconnect();

    /**
     * Send shell command to the server
     * @param command Shell command to execute on server
     * @return Response message
     */
    void shell(const std::string& command);

    /**
     * Handle message from server
     * @param msg Received message
     * @return Response
     */
    std::string handle_new_message(std::string msg, const std::string& ip_port) override;
};
