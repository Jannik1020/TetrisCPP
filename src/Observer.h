//
// Created by jannikthiele on 27.04.25.
//

#ifndef OBSERVER_H
#define OBSERVER_H
#include <optional>
#include <SFML/Window/Event.hpp>

#include "Observable.h"

class Observer {
    Observable* subject;
public:
    explicit Observer(Observable* subject):subject(subject) {
        subject->registerNewListener(this);
    }
    virtual void update(std::optional<sf::Event> event) = 0;
    virtual ~Observer();
};



#endif
