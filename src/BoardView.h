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

    static const int numberColumns{12};
    static const int numberRows{18};

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void initVertexArray();

public:
    explicit BoardView(float width);


    float getWidth() const;
    float getHeight() const;

    float getBorderWidth() const;
    void setBorderWidth(float border_width);

    float getTileWidth() const {return width / numberColumns;}
    float getTileHeight() const {return getTileWidth();}
};


#endif //BOARDVIEW_H
