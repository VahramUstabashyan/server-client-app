#pragma once

#include <memory>
#include <boost/asio.hpp>

#include "ConnectionObserver.hpp"


class Observable {
protected:
    /// ConnectionObserver pointer
    std::weak_ptr<ConnectionObserver> observer_weak;
public:
    /**
     * Set observer
     * @param o The observer to set
     */
    void set_observer(std::weak_ptr<ConnectionObserver> o);
};
