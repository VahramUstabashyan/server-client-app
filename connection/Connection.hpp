#pragma once

#include <iostream>
#include <boost/asio.hpp>

#include "../observer/Observable.hpp"

using boost::asio::ip::tcp;


class Connection : public Observable {
private:
    /// Const random-generated string to mark the end of the message
    const std::string END_OF_MESSAGE = "MhDKYv0BenZ9qLGHoG4PlClGarO4H8Vww15By2xz";

    /// TCP socket pointer for current connection
    std::unique_ptr<tcp::socket> socket_ptr;

    boost::asio::streambuf read_buf;
    std::string read_msg;
public:
    /// Default constructor
    Connection() = default;

    /**
     * Constructor
     * @param socket_ptr TCP socket pointer
     */
    explicit Connection(std::unique_ptr<tcp::socket> socket_ptr);

    /**
     * Read data asynchronously
     */
    void read();

    /**
     * Get last read message
     * @return last message
     */
    std::string get_last_msg() const;

    /**
     * Write data asynchronously
     * @param msg Data to write
     */
    void write(const std::string& msg);

    /**
     * Same as `write` but add '\n' at the end
     * @param msg Data to write
     */
    void writeln(const std::string& msg);

    /**
     * Get IP address and port of the remote endpoint in `address:port` format
     * @return Remote IP address and port as string
     */
    std::string remote_ip_port() const;

    /**
     * Whether the connection is open
     * @return Connection status
     */
    bool is_open();

    /**
     * Close the socket
     */
    void close();

    /**
     * Update connection observer
     */
    void update();

private:
    /**
     * Handle reading data
     * @param err Error code
     * @param bytes_read Number of read bytes
     */
    void handle_read(boost::system::error_code err, std::size_t bytes_read);

    /**
     * Handle writing data
     * @param err Error code
     * @param bytes_written Number of bytes written
     */
    void handle_write(boost::system::error_code err, std::size_t bytes_written) const;
};
