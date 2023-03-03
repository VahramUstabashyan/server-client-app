#pragma once

#include <iostream>
#include <memory>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

class Connection;


class ConnectionObserver : public std::enable_shared_from_this<ConnectionObserver> {
public:
    /**
     * Handle new message from connection
     * @param msg Received message
     * @return Response
     */
    virtual std::string handle_new_message(std::string msg, const std::string& ip_port) = 0;

protected:
    static void not_connected();

    static void already_connected();
};