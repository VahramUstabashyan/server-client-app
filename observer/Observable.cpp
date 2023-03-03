#include "Observable.hpp"

void Observable::set_observer(std::weak_ptr<ConnectionObserver> o) {
    observer_weak = std::move(o);
}
