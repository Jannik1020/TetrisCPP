//
// Created by jannikthiele on 27.04.25.
//

#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include "BoardModel.h"
#include "Observable.h"
#include "TileGrid.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"


class BoardView final : public sf::Drawable, public sf::Transformable, public Observable {
    const TileGrid &board;
    const ActiveTetromino &activeTetromino;

    sf::VertexArray vertices;

    float width{};
    float height{};
    float borderWidth{};

    float tileWidth;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void initVertexArray();

public:
    explicit BoardView(float width, const TileGrid &board, const ActiveTetromino&activeTetromino);

    void setWidth(float width);
    void setHeight(float height);
    float getWidth() const;

    float getHeight() const;

    float getBorderWidth() const;

    void setBorderWidth(float border_width);

    float getTileWidth() const { return tileWidth; }
    float getTileHeight() const { return getTileWidth(); }
};


#endif //BOARDVIEW_H
