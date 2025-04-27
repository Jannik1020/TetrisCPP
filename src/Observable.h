//
// Created by jannikthiele on 27.04.25.
//

#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include <list>
#include <optional>
#include <SFML/Window/Event.hpp>

class Observer;
class Observable {
    std::list<Observer *> listeners;

public:
    void registerNewListener(Observer* listener);
    void unregisterListener(Observer* listener);
    void notifyListeners(const std::optional<sf::Event> &event) const;
};


#endif
