//
// Created by jannikthiele on 27.04.25.
//

#include "TileRectangle.h"
#include "SFML/Graphics/RenderTarget.hpp"

void TileRectangle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(vertices, states);
}

TileRectangle::TileRectangle(float width, float height, sf::Color color): width(width), height(height), color(color),
                                                                          vertices(sf::VertexArray(
                                                                              sf::PrimitiveType::TriangleStrip, 4)) {
    vertices[0].position = sf::Vector2f(0.f, 0.f);
    vertices[1].position = sf::Vector2f(width, 0.f);
    vertices[2].position = sf::Vector2f(0.f, height);
    vertices[3].position = sf::Vector2f(width, height);
}
