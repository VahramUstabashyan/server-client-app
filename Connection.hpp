#pragma once

#include <boost/asio.hpp>

using boost::asio::ip::tcp;


class Connection {
private:
    /// TCP socket pointer for current connection
    std::shared_ptr<tcp::socket> socket_ptr;

public:
    /**
     * Constructor
     * @param socket_ptr TCP socket pointer
     */
    explicit Connection(std::shared_ptr<tcp::socket> socket_ptr);

    /**
     * Read data asynchronously
     */
    void read();

    /**
     * Write data asynchronously
     * @param msg Data to write
     */
    void write(std::string msg);

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
