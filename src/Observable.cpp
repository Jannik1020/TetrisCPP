//
// Created by jannikthiele on 27.04.25.
//

#include "Observable.h"
#include "Observer.h"

void Observable::registerNewListener(Observer* const listener) {
    this->listeners.emplace_back(listener);
}

void Observable::unregisterListener(Observer* const listener) {
    this->listeners.remove(listener);
}

void Observable::notifyListeners(const std::optional<sf::Event> &event) const {
    for (Observer* listener: listeners) {
        listener->update(event);
    }
}

