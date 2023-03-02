#pragma once

#include <memory>
#include <boost/asio.hpp>

#include "ConnectionObserver.hpp"


class Observable {
protected:
    /// ConnectionObserver pointer
    std::shared_ptr<ConnectionObserver> observer;
public:
    /**
     * Set observer
     * @param o The observer to set
     */
    void set_observer(std::shared_ptr<ConnectionObserver> o);
};
