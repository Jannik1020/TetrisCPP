//
// Created by jannikthiele on 27.04.25.
//

#include "BoardView.h"

#include <sys/stat.h>

#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

void BoardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    /*
     * Draw Tetris Board
     */

    states.transform *= getTransform();
    //states.texture = ...;

    target.draw(vertices, states);

    sf::VertexArray tile(sf::PrimitiveType::TriangleStrip, 4);

    for (int row = 0; row < board.rows; row++) {
        for (int col = 0; col < board.columns; col++) {
            if (board.getCellAt(row, col).isCellOccupied()) {
                float originX = borderWidth + col * tileWidth;
                float originY = row * tileWidth;

                tile[0].position = sf::Vector2f(originX, originY);
                tile[1].position = sf::Vector2f(originX, originY + tileWidth);
                tile[2].position = sf::Vector2f(originX + tileWidth, originY);
                tile[3].position = sf::Vector2f(originX + tileWidth, originY + tileWidth);

                for (int i = 0; i < 4; i++) {
                    tile[i].color = board.getCellAt(row, col).getTile()->getColor();
                }

                target.draw(tile, states);
            }
        }
    }


    /*
     * Draw active Tetromino
     */

    const TileGrid &activeTetrominoGrid = activeTetromino.tetromino.getTileGrid();

    for (int row = 0; row < activeTetrominoGrid.rows; row++) {
        for (int col = 0; col < activeTetrominoGrid.columns; col++) {
            if (activeTetrominoGrid.getCellAt(row, col).isCellOccupied()) {
                float originX = borderWidth + col * tileWidth + activeTetromino.x * tileWidth;
                float originY = row * tileWidth + activeTetromino.y * tileWidth;

                tile[0].position = sf::Vector2f(originX, originY);
                tile[1].position = sf::Vector2f(originX, originY + tileWidth);
                tile[2].position = sf::Vector2f(originX + tileWidth, originY);
                tile[3].position = sf::Vector2f(originX + tileWidth, originY + tileWidth);

                for (int i = 0; i < 4; i++) {
                    tile[i].color = activeTetrominoGrid.getCellAt(row, col).getTile()->getColor();
                }

                target.draw(tile, states);
            }
        }
    }

    /*
     * Draw preview Queue
     */

    float previewTileWidth = tileWidth * 0.6;

    std::queue<ActiveTetromino> copyQueue = tetrominoQueue;
    copyQueue.pop();

    float offsetX = previewTileWidth;
    float offsetY = 0;

    while (!copyQueue.empty()) {
        TileGrid const &previewGrid = copyQueue.front().tetromino.getTileGrid();
        int firstOccupiedCol = copyQueue.front().tetromino.getFirstOccupiedGridColumn();
        int firstOccupiedRow = copyQueue.front().tetromino.getFirstOccupiedGridRow();
        int lastOccupiedRow = copyQueue.front().tetromino.getLastOccupiedGridRow();

        // if (previewGrid.columns == 4) offsetX = 0;
        // else offsetX = previewTileWidth;

        for (int row = 0; row < previewGrid.rows; row++) {
            for (int col = 0; col < previewGrid.columns; col++) {

                if (previewGrid.getCellAt(row, col).isCellOccupied()) {
                    float originX = width + offsetX + (col - firstOccupiedCol) * previewTileWidth;
                    float originY = offsetY + (row-firstOccupiedRow) * previewTileWidth;

                    tile[0].position = sf::Vector2f(originX, originY);
                    tile[1].position = sf::Vector2f(originX, originY + previewTileWidth);
                    tile[2].position = sf::Vector2f(originX + previewTileWidth, originY);
                    tile[3].position = sf::Vector2f(originX + previewTileWidth, originY + previewTileWidth);

                    for (int i = 0; i < 4; i++) {
                        tile[i].color = previewGrid.getCellAt(row, col).getTile()->getColor();
                    }

                    target.draw(tile, states);
                }
            }
        }
        copyQueue.pop();
        offsetY+=(lastOccupiedRow-firstOccupiedRow+1)*previewTileWidth+previewTileWidth;
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

    vertices[6].position = sf::Vector2f(width, 0.f); // right border : top right
    vertices[7].position = sf::Vector2f(width - borderWidth, 0.f); //right border: top left
}

BoardView::BoardView(float width, const TileGrid &board, const ActiveTetromino &activeTetromino,
                     const std::queue<ActiveTetromino> &tetrominoQueue): board(board),
                                                                         activeTetromino(activeTetromino),
                                                                         tetrominoQueue(tetrominoQueue),
                                                                         vertices(sf::VertexArray(
                                                                             sf::PrimitiveType::TriangleStrip, 8)),
                                                                         width(width),
                                                                         borderWidth(10) {
    tileWidth = (width - 2 * borderWidth) / static_cast<float>(board.columns);
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
    } else {
        this->width = 500;
    }

    tileWidth = (width - 2 * borderWidth) / static_cast<float>(board.columns);
    height = tileWidth * static_cast<float>(board.rows) + borderWidth;
    initVertexArray();
}

void BoardView::setHeight(float height) {
    if (height > 500) {
        this->height = height;
    } else {
        this->height = 500;
    }

    tileWidth = (this->height - borderWidth) / static_cast<float>(board.rows);
    width = tileWidth * static_cast<float>(board.columns) + 2 * borderWidth;
    initVertexArray();
}
