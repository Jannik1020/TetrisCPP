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
