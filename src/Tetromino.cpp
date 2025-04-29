//
// Created by jannikthiele on 28.04.25.
//

#include <iostream>
#include "Tetromino.h"

Tetromino::Tetromino(const TetrominoShape::TetrominoShapeGrid &shape, sf::Color color): grid(TileGrid(
        shape.rows, shape.columns)), color(color) {
    for (int row = 0; row < shape.rows; row++) {
        for (int col = 0; col < shape.columns; col++) {
            if (shape.getCellAt(row, col))
                grid.getCellAt(row, col).attachTile(new Tile(color));
        }
    }
}

int Tetromino::getFirstOccupiedGridRow() {
    for (int row = 0; row < grid.rows; row++) {
        for (int col = 0; col < grid.columns; col++) {
            if (grid.getCellAt(row, col).isCellOccupied()) {
                return row;
            }
        }
    }
    return -1;
}

int Tetromino::getLastOccupiedGridRow() {
    for (int row = grid.rows - 1; row >= 0; row--) {
        for (int col = 0; col < grid.columns; col++) {
            if (grid.getCellAt(row, col).isCellOccupied()) {
                return row;
            }
        }
    }
    return -1;
}

int Tetromino::getFirstOccupiedGridColumn() {
    for (int col = 0; col < grid.columns; col++) {
        for (int row = 0; row < grid.rows; row++) {
            if (grid.getCellAt(row, col).isCellOccupied()) {
                return col;
            }
        }
    }
    return -1;
}

int Tetromino::getLastOccupiedGridColumn() {
    for (int col = grid.columns-1; col >= 0; col--) {
        for (int row = 0; row < grid.rows; row++) {
            if (grid.getCellAt(row, col).isCellOccupied()) {
                return col;
            }
        }
    }
    return -1;
}

void Tetromino::rotate90Clockwise() {
    std::cout << "rotated" <<std::endl;
    TileGrid rotatedGrid(grid.rows, grid.columns);
    for (int row = 0; row < grid.rows; row++) {
        for (int col = 0; col < grid.columns; col ++) {
            if (grid.getCellAt(row,col).isCellOccupied())
            grid.getCellAt(row, col).transferTile(rotatedGrid.getCellAt(col, rotatedGrid.columns - row-1));
        }
    }

    for (int row = 0; row < grid.rows; row++) {
        for (int col = 0; col < grid.columns; col ++) {
            if (rotatedGrid.getCellAt(row,col).isCellOccupied())
            rotatedGrid.getCellAt(row, col).transferTile(grid.getCellAt(row, col));
            else
                grid.getCellAt(row,col).detachTile();
        }
    }
}
