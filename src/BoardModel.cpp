//
// Created by jannikthiele on 28.04.25.
//

#include "BoardModel.h"

bool BoardModel::checkTetrominoCollision() const{
    Position expectedPosition = activeMoveStrategy->move(activeTetrominoPosition);

    int x = expectedPosition.x;
    int y = expectedPosition.y;
    int boundingSize = activeTetromino->getBoundingSize();
    TileGrid tetrominoGrid = activeTetromino->getTileGrid();

    for (int row = 0; row < boundingSize; row++) {
        for (int col = 0; col < boundingSize; col++) {
            if (tetrominoGrid.getCellAt(row, col).isCellOccupied() &&
                grid.getCellAt(y + row, x + col).isCellOccupied())
                return true;
        }
    }
    return false;
}

bool BoardModel::checkWallCollision() const {
    Position expectedPosition = activeMoveStrategy->move(activeTetrominoPosition);
    if (expectedPosition.x < 0 || expectedPosition.x >= grid.columns) return true;
    return false;
}

void BoardModel::settleTetromino() {
    int x = activeTetrominoPosition.x;
    int y = activeTetrominoPosition.y;
    int boundingSize = activeTetromino->getBoundingSize();
    TileGrid tetrominoGrid = activeTetromino->getTileGrid();

    for (int row = 0; row < boundingSize; row++) {
        for (int col = 0; col < boundingSize; col++) {
            tetrominoGrid.getCellAt(row, col).transferTile(grid.getCellAt(y + row, x + col));
        }
    }
}


void BoardModel::moveActiveTetromino(MoveStrategy * newMoveStrategy) {
    activeMoveStrategy = newMoveStrategy;

    if (checkWallCollision()) {
        activeMoveStrategy = moveDownStrategy;
    }

    if (checkTetrominoCollision() || checkBottomCollision()) {
        settleTetromino();
        //resetRound? --> moveDownStrategy, spawnNewTetromino, adjust activeTetrominoPosition
        spawnNewTetromino();
        return;
    }

    activeTetrominoPosition = activeMoveStrategy->move(activeTetrominoPosition);
}

void BoardModel::moveActiveTetrominoRight() {
    moveActiveTetromino(moveRightStrategy);
}

void BoardModel::moveActiveTetrominoLeft() {
    moveActiveTetromino(moveLeftStrategy);
}

void BoardModel::moveActiveTetrominoDown() {
    moveActiveTetromino(moveDownStrategy);
}

void BoardModel::rotateActiveTetromino() {
}

void BoardModel::spawnNewTetromino() {
}
