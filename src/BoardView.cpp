//
// Created by jannikthiele on 27.04.25.
//

#include "BoardView.h"

#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

void BoardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    //states.texture = ...;

    target.draw(vertices, states);
}

void BoardView::initVertexArray() {
    vertices[0].position = sf::Vector2f(0.f, 0.f); // left border: top left
    vertices[1].position = sf::Vector2f(borderWidth, 0.f); // left border: top right
    vertices[2].position = sf::Vector2f(0.f, height); // left border: bottom left

    vertices[3].position = sf::Vector2f(borderWidth, height - borderWidth); // left border: bottom right | inner
    vertices[4].position = sf::Vector2f(width - borderWidth, height); // right border: bottom right
    vertices[5].position = sf::Vector2f(width - 2 * borderWidth, height - borderWidth);
    // right border: bottom left | inner

    vertices[6].position = sf::Vector2f(width - borderWidth, 0.f); // right border : top right
    vertices[7].position = sf::Vector2f(width - 2 * borderWidth, 0.f); //right border: top left
}

BoardView::BoardView(float width, float numberColumns, float numberRows): vertices(sf::VertexArray(
                                       sf::PrimitiveType::TriangleStrip, 8)),
                                   width(width), height((width / numberColumns) * numberRows), borderWidth(10), tileWidth(width / numberColumns) {
    initVertexArray();
}


float BoardView::getWidth() const {
    return width;
}

float BoardView::getHeight() const {
    return height;
}

float BoardView::getBorderWidth() const {
    return borderWidth;
}

void BoardView::setBorderWidth(float border_width) {
    borderWidth = border_width;
}
