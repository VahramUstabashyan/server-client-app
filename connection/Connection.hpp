#pragma once

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


class Connection {
private:
    /// TCP socket pointer for current connection
    std::unique_ptr<tcp::socket> socket_ptr;

    boost::asio::streambuf read_buf;
    std::string read_msg;
public:
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
     * Write data asynchronously
     * @param msg Data to write
     */
    void write(std::string msg);

    /**
     * Get IP address and port of the remote endpoint in `address:port` format
     * @return Remote IP address and port as string
     */
    std::string remote_ip_port();

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
    void handle_write(boost::system::error_code err, std::size_t bytes_written);
};
