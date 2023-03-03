#include "ConnectionObserver.hpp"

void ConnectionObserver::not_connected() {
    std::cerr << "Connection not established. Aborting...\n";
}

void ConnectionObserver::already_connected() {
    std::cerr << "Connection already exists.\n";
}