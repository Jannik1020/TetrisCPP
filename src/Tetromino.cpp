//
// Created by jannikthiele on 28.04.25.
//

#include "Tetromino.h"
Tetromino::Tetromino(TetrominoShape::TetrominoShapeGrid& shape, sf::Color color): grid(shape.rows, shape.columns), color(color) {
    for (int row = 0; row < shape.rows; row++) {
        for (int col = 0; col < shape.columns; col ++) {
            if (shape.getCellAt(row, col))
                grid.getCellAt(row, col).attachTile(new Tile(color));
        }
    }
}