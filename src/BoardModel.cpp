//
// Created by jannikthiele on 28.04.25.
//

#include "BoardModel.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>

class TetrisScore {

};

bool BoardModel::checkTetrominoCollision() const{
    ActiveTetromino previewTetromino = activeMoveStrategy->move(activeTetromino);
    //Position expectedPosition = activeMoveStrategy->move(activeTetrominoPosition);

    int x = previewTetromino.x;
    int y = previewTetromino.y;
    TileGrid tetrominoGrid = previewTetromino.tetromino.getTileGrid();

    for (int row = previewTetromino.tetromino.getFirstOccupiedGridRow(); row < previewTetromino.tetromino.getLastOccupiedGridRow()+1; row++) {
        for (int col = previewTetromino.tetromino.getFirstOccupiedGridColumn(); col < previewTetromino.tetromino.getLastOccupiedGridColumn()+1; col++) {
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
    ActiveTetromino previewTetromino = activeMoveStrategy->move(activeTetromino);
    //Position expectedPosition = activeMoveStrategy->move(activeTetrominoPosition);
    if (previewTetromino.x + previewTetromino.tetromino.getFirstOccupiedGridColumn() < 0 ||
        previewTetromino.x + previewTetromino.tetromino.getLastOccupiedGridColumn() >= grid.columns) return true;
    return false;
}

void BoardModel::settleTetromino() {
    int x = activeTetromino.x;
    int y = activeTetromino.y;
    TileGrid tetrominoGrid = activeTetromino.tetromino.getTileGrid();

    for (int row = 0; row <= activeTetromino.tetromino.getLastOccupiedGridRow(); row++) {
        for (int col = 0; col <= activeTetromino.tetromino.getLastOccupiedGridColumn(); col++) {
            tetrominoGrid.getCellAt(row, col).transferTile(grid.getCellAt(y + row, x + col));
        }
    }

    tetrominoQueue.pop();
}


void BoardModel::moveActiveTetromino(TetrominoMoveStrategy * newMoveStrategy) {
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
    activeTetromino = activeMoveStrategy->move(activeTetromino);
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
    moveActiveTetromino(rotateStrategy);
}

void BoardModel::spawnNextTetromino() {
    activeTetromino = tetrominoQueue.front();
    activeTetromino.x = numberColumns / 2 - activeTetromino.tetromino.getBoundingSize() / 2;
    activeTetromino.y = 0 - activeTetromino.tetromino.getFirstOccupiedGridRow();

    if (checkTetrominoCollision()) {
        std::cout << "Game Over" << std::endl;
        exit(1);
    }
}

bool BoardModel::checkBottomCollision() {
    ActiveTetromino previewTetromino = activeMoveStrategy->move(activeTetromino);
    //Position expectedPosition = activeMoveStrategy->move(activeTetrominoPosition);
    int lastOccupiedRow = previewTetromino.tetromino.getLastOccupiedGridRow();
    if (previewTetromino.y + lastOccupiedRow >= grid.rows) return true;
    return false;
}

void BoardModel::resetBoard() {
    activeMoveStrategy = moveDownStrategy;
    fillTetrominoQueue();
    spawnNextTetromino();
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

void BoardModel::fillTetrominoQueue() {
    while (tetrominoQueue.size() < tetrominoQueueLength) {
        std::random_device::result_type random =std::random_device()() % 7;
        tetrominoQueue.emplace(Tetromino(TetrominoShape::Shapes[random],TetrominoShape::ShapeColors[random]));
    }
}
