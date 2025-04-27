#include <SFML/Graphics.hpp>
#include <X11/X.h>

#include "BoardView.h"


int main() {
    sf::RenderWindow window(sf::VideoMode({2000, 2000}), "SFML works!");

    BoardView board(800, 1200);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto *resized = event->getIf<sf::Event::Resized>()) {
                // update the view to the new size of the window
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
                board.setPosition(sf::Vector2f(window.getSize().x/2 - board.getWidth()/2, window.getSize().y/2-board.getHeight()/2));
            }
        }

        window.clear();
        window.draw(board);
        window.display();
    }
}
