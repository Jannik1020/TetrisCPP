#include <iostream>
#include <SFML/Graphics.hpp>
#include <X11/X.h>

#include "BoardController.h"
#include "BoardModel.h"
#include "BoardView.h"
#include "Tetromino.h"
#include "TileGrid.h"


int main() {
    sf::RenderWindow window(sf::VideoMode({2000, 2000}), "Tetris");

    BoardModel board;
    BoardView boardView(1400, board);
    BoardController controller(board);

    int tickSpeed = 1000;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        while (elapsed.asMilliseconds() < tickSpeed) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window.close();
                if (const auto *resized = event->getIf<sf::Event::Resized>()) {
                    // update the view to the new size of the window
                    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                    window.setView(sf::View(visibleArea));
                    boardView.setPosition(sf::Vector2f(window.getSize().x / 2 - boardView.getWidth() / 2,
                                                       window.getSize().y / 2 - boardView.getHeight() / 2));
                    boardView.setHeight(window.getSize().y * (0.8));
                }
                sf::Clock timer;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                    timer.restart();
                    controller.moveTetrominoLeft();
                    std::cout << "Left " << timer.getElapsedTime().asMicroseconds() << std::endl;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                    timer.restart();
                    controller.moveTetrominoRight();
                    std::cout << "Right " << timer.getElapsedTime().asMicroseconds() << std::endl;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                    timer.restart();
                    controller.moveTetrominoDown();
                    std::cout << "Down " << timer.getElapsedTime().asMicroseconds() << std::endl;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                    timer.restart();
                    controller.rotateTetromino();
                    std::cout << "Rotate " << timer.getElapsedTime().asMicroseconds() << std::endl;
                }
            }

            controller.deleteCompleteRows();
            window.clear();
            window.draw(boardView);
            window.display();
            elapsed = clock.getElapsedTime();
        }

        controller.moveTetrominoDown();
        clock.reset();
        // tickSpeed -= 0.2;
        // window.clear();
        // window.draw(boardView);
        // window.display();
    }
}
