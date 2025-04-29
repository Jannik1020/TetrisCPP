//
// Created by jannikthiele on 28.04.25.
//

#include "BoardModel.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>

bool BoardModel::checkTetrominoCollision() const{
    Position expectedPosition = activeMoveStrategy->move(activeTetrominoPosition);

    int x = expectedPosition.x;
    int y = expectedPosition.y;
    int boundingSize = activeTetromino->getBoundingSize();
    TileGrid tetrominoGrid = activeTetromino->getTileGrid();

    for (int row = activeTetromino->getFirstOccupiedGridRow(); row < activeTetromino->getLastOccupiedGridRow()+1; row++) {
        for (int col = activeTetromino->getFirstOccupiedGridColumn(); col < activeTetromino->getLastOccupiedGridColumn()+1; col++) {
            if (y+row >= grid.rows) break;
            if (x+col >= grid.columns) break;
            if (x+col < 0) break;
            if (y+row < 0) break;

            if (tetrominoGrid.getCellAt(row, col).isCellOccupied() &&
                grid.getCellAt(y + row, x + col).isCellOccupied())
                return true;
        }
    }
    return false;
}

bool BoardModel::checkWallCollision() const {
    Position expectedPosition = activeMoveStrategy->move(activeTetrominoPosition);
    if (expectedPosition.x + activeTetromino->getFirstOccupiedGridColumn() < 0 ||
        expectedPosition.x + activeTetromino->getLastOccupiedGridColumn() >= grid.columns) return true;
    return false;
}

void BoardModel::settleTetromino() {
    int x = activeTetrominoPosition.x;
    int y = activeTetrominoPosition.y;
    TileGrid tetrominoGrid = activeTetromino->getTileGrid();

    for (int row = 0; row <= activeTetromino->getLastOccupiedGridRow(); row++) {
        for (int col = 0; col <= activeTetromino->getLastOccupiedGridColumn(); col++) {
            tetrominoGrid.getCellAt(row, col).transferTile(grid.getCellAt(y + row, x + col));
        }
    }
}


void BoardModel::moveActiveTetromino(MoveStrategy * newMoveStrategy) {
    bool noCollision = true;

    activeMoveStrategy = newMoveStrategy;



    if (checkWallCollision()) {
        activeMoveStrategy = moveDownStrategy;
        std::cout << "Wall collision detected" << std::endl;
        noCollision = false;
    }

    if (activeMoveStrategy == moveDownStrategy) {
        if (checkTetrominoCollision() || checkBottomCollision()) {
            std::cout << "Tetromino collision detected" << std::endl;
            settleTetromino();
            resetBoard();
            return;
        }
    }
    else {
        if (checkTetrominoCollision() || checkBottomCollision()) {
            activeMoveStrategy = moveDownStrategy;
            std::cout << "Wall collision detected" << std::endl;
            noCollision = false;
        }
    }

    if (noCollision)
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
    activeTetromino->rotate90Clockwise();
}

void BoardModel::spawnNewTetromino() {
    delete activeTetromino;
    std::random_device::result_type random =std::random_device()() % 7;
    activeTetromino = new Tetromino(TetrominoShape::Shapes[random],TetrominoShape::ShapeColors[random]);
    activeTetrominoPosition.x = numberColumns / 2 - activeTetromino->getBoundingSize() / 2;
    activeTetrominoPosition.y = 0 - activeTetromino->getFirstOccupiedGridRow();

    if (checkTetrominoCollision()) {
        std::cout << "Game Over" << std::endl;
        delete activeTetromino;
        activeTetromino = nullptr;
    }
}

bool BoardModel::checkBottomCollision() {
    Position expectedPosition = activeMoveStrategy->move(activeTetrominoPosition);
    int lastOccupiedRow = activeTetromino->getLastOccupiedGridRow();
    if (expectedPosition.y + lastOccupiedRow >= grid.rows) return true;
    return false;
}

void BoardModel::resetBoard() {
    activeMoveStrategy = moveDownStrategy;
    spawnNewTetromino();
}

bool BoardModel::isRowComplete(std::vector<TileGridCell>& row) const{
    for (TileGridCell cell: row) {
        if (cell.isCellOccupied() == false) return false;
    }
    return true;

}
void BoardModel::deleteCompleteRows() {
    for (int i = 0; i < grid.rows; i++) {
        if (isRowComplete(grid[i])) {
            grid.popRow(i);
            grid.pushEmptyRow();
        }
    }
}
