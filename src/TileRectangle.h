//
// Created by jannikthiele on 27.04.25.
//

#ifndef TILERECTANGLE_H
#define TILERECTANGLE_H
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"


class TileRectangle : sf::Drawable, sf::Transformable {
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    float width;
    float height;
    sf::Color color;
    sf::VertexArray vertices;

public:
    TileRectangle(float width, float height, sf::Color color);
};


#endif //TILEVIEW_H
