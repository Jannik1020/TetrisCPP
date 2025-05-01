//
// Created by jannikthiele on 27.04.25.
//

#include "BoardView.h"

#include <sys/stat.h>

#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

void BoardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    //states.texture = ...;

    target.draw(vertices, states);

    sf::VertexArray tile(sf::PrimitiveType::TriangleStrip, 4);

    for (int row = 0; row < board.rows; row++) {
        for (int col = 0; col < board.columns; col++) {
            if ( board.getCellAt(row, col).isCellOccupied()) {
                float originX = borderWidth + col* tileWidth;
                float originY = row * tileWidth;

                tile[0].position = sf::Vector2f(originX, originY);
                tile[1].position = sf::Vector2f(originX, originY+tileWidth);
                tile[2].position = sf::Vector2f(originX+tileWidth, originY);
                tile[3].position = sf::Vector2f(originX+tileWidth, originY+tileWidth);

                for (int i = 0; i < 4; i++) {
                    tile[i].color = board.getCellAt(row,col).getTile()->getColor();
                }

                target.draw(tile, states);
            }
        }
    }

    const TileGrid & activeTetrominoGrid = activeTetromino.tetromino.getTileGrid();

    for (int row = 0; row < activeTetrominoGrid.rows; row++) {
        for (int col = 0; col < activeTetrominoGrid.columns; col++) {
            if ( activeTetrominoGrid.getCellAt(row, col).isCellOccupied()) {
                float originX = borderWidth + col * tileWidth + activeTetromino.x * tileWidth;
                float originY = row * tileWidth + activeTetromino.y * tileWidth;

                tile[0].position = sf::Vector2f(originX, originY);
                tile[1].position = sf::Vector2f(originX, originY+tileWidth);
                tile[2].position = sf::Vector2f(originX+tileWidth, originY);
                tile[3].position = sf::Vector2f(originX+tileWidth, originY+tileWidth);

                for (int i = 0; i < 4; i++) {
                    tile[i].color = activeTetrominoGrid.getCellAt(row,col).getTile()->getColor();
                }

                target.draw(tile, states);
            }
        }
    }

}

void BoardView::initVertexArray() {
    vertices[0].position = sf::Vector2f(0.f, 0.f); // left border: top left
    vertices[1].position = sf::Vector2f(borderWidth, 0.f); // left border: top right
    vertices[2].position = sf::Vector2f(0.f, height); // left border: bottom left

    vertices[3].position = sf::Vector2f(borderWidth, height - borderWidth); // left border: bottom right | inner
    vertices[4].position = sf::Vector2f(width, height); // right border: bottom right
    vertices[5].position = sf::Vector2f(width - borderWidth, height - borderWidth);
    // right border: bottom left | inner

    vertices[6].position = sf::Vector2f(width , 0.f); // right border : top right
    vertices[7].position = sf::Vector2f(width - borderWidth, 0.f); //right border: top left
}

BoardView::BoardView(float width, const TileGrid & board, const ActiveTetromino  &activeTetromino):
                                    board(board),
                                    activeTetromino(activeTetromino),
                                    vertices(sf::VertexArray(sf::PrimitiveType::TriangleStrip, 8)),
                                    width(width),
                                    borderWidth(10) {

    tileWidth = (width-2*borderWidth) / static_cast<float>(board.columns);
    height = tileWidth * static_cast<float>(board.rows) + borderWidth;
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

void BoardView::setWidth(float width) {
    if (width > 500) {
        this->width = width;
    }
    else {
        this->width = 500;
    }

    tileWidth = (width-2*borderWidth) / static_cast<float>(board.columns);
    height = tileWidth * static_cast<float>(board.rows) + borderWidth;
    initVertexArray();
}

void BoardView::setHeight(float height) {
    if (height > 500) {
        this->height = height;
    }
    else {
        this->height = 500;
    }

    tileWidth = (this->height-borderWidth) / static_cast<float>(board.rows);
    width = tileWidth * static_cast<float>(board.columns) + 2*borderWidth;
    initVertexArray();
}
