#include "Observable.hpp"

void Observable::set_observer(std::shared_ptr<ConnectionObserver> o) {
    observer = std::move(o);
}
