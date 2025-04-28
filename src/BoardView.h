//
// Created by jannikthiele on 27.04.25.
//

#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include "Observable.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"


class BoardView final : public sf::Drawable, public sf::Transformable, public Observable {
    sf::VertexArray vertices;
    float width{};
    float height{};
    float borderWidth{};

    float tileWidth;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void initVertexArray();

public:
    explicit BoardView(float width, float numberColumns, float numberRows);


    float getWidth() const;
    float getHeight() const;

    float getBorderWidth() const;
    void setBorderWidth(float border_width);

    float getTileWidth() const {return tileWidth;}
    float getTileHeight() const {return getTileWidth();}
};


#endif //BOARDVIEW_H
