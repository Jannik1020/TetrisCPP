//
// Created by jannikthiele on 28.04.25.
//

#include "TileGrid.h"

void TileGridCell::attachTile(Tile *tile) {
    if (tile != nullptr) {
        this->tile = tile;
        isOccupied = true;
    }
}

void TileGridCell::detachTile() {
    if (this->tile != nullptr) {
        delete this->tile;
        this->tile = nullptr;
        isOccupied = false;
    }
}

void TileGridCell::transferTile(TileGridCell & cell) {
    cell.attachTile(this->tile);
    this->tile=nullptr;
    isOccupied = false;
}

#include <iostream>

std::ostream &operator<<(std::ostream &os, const Grid<TileGridCell> &grid) {
    for (int row = 0; row < grid.rows; ++row) {
        for (int col = 0; col < grid.columns; ++col) {
            os << (grid.getCellAt(row, col).isCellOccupied() ? "X" : ".") << " ";
        }
        os << "\n";
    }
    return os;
}