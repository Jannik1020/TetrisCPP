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
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::VertexArray vertices;
    float width{};
    float height{};
    float borderWidth{};

public:
    BoardView(float width, float height);
 float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

    float getBorderWidth() const;

    void setBorderWidth(float border_width);
};


#endif //BOARDVIEW_H
