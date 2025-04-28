#include <iostream>
#include <SFML/Graphics.hpp>
#include <X11/X.h>

#include "BoardView.h"
#include "TileGrid.h"


int main() {
    sf::RenderWindow window(sf::VideoMode({2000, 2000}), "SFML works!");

    BoardView board(800, 12, 20);
    TileGrid grid(20, 12);
    grid.getCellAt(19,11).attachTile(new Tile());
    grid[19][11].transferTile(grid[0][0]);
    std::cout << grid[19][11].isCellOccupied() << std::endl;
    std::cout << grid[0][0].isCellOccupied() << std::endl;

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
