#include "ConnectionObserver.hpp"

void ConnectionObserver::not_connected() {
    std::cerr << "Connection not established. Aborting...\n";
}