//
// Created by jannikthiele on 28.04.25.
//

#ifndef BOARDMODEL_H
#define BOARDMODEL_H
#include <queue>

#include "Tetromino.h"
#include "TileGrid.h"

struct Position {
    int x;
    int y;

    Position(): x(0), y(0) {
    }

    Position(int x, int y): x(x), y(y) {
    }
};

class TetrisScore {
    int score_;
    int linesCleared;

public:
    TetrisScore(): score_(0), linesCleared(0) {
    }

    void score(int linesCleared) { this->linesCleared += linesCleared; }
    int getScore() const { return linesCleared; }
};


struct ActiveTetromino {
    Tetromino tetromino;
    int x = 0;
    int y = 0;

    ActiveTetromino(): tetromino(Tetromino()) {
    }

    explicit ActiveTetromino(const Tetromino &tetromino): tetromino(tetromino) {
    }

    ActiveTetromino(ActiveTetromino const &other): tetromino(other.tetromino), x(other.x), y(other.y) {
    }

    ActiveTetromino &operator=(const ActiveTetromino &tetromino) {
        if (this == &tetromino) {
            return *this;
        }

        this->tetromino = Tetromino(tetromino.tetromino);
        x = tetromino.x;
        y = tetromino.y;

        return *this;
    }
};

class TetrominoMoveStrategy {
public:
    virtual ~TetrominoMoveStrategy() = default;

    virtual ActiveTetromino move(ActiveTetromino activeTetromino) =0;
};

class TetrominoMoveRightStrategy : public TetrominoMoveStrategy {
public:
    ActiveTetromino move(ActiveTetromino activeTetromino) override {
        activeTetromino.x += 1;
        return activeTetromino;
    }
};

class TetrominoMoveLeftStrategy : public TetrominoMoveStrategy {
public:
    ActiveTetromino move(ActiveTetromino activeTetromino) override {
        activeTetromino.x -= 1;
        return activeTetromino;
    }
};

class TetrominoMoveDownStrategy : public TetrominoMoveStrategy {
public:
    ActiveTetromino move(ActiveTetromino activeTetromino) override {
        activeTetromino.y += 1;
        return activeTetromino;
    }
};


class TetrominoRotateStrategy : public TetrominoMoveStrategy {
public:
    ActiveTetromino move(ActiveTetromino activeTetromino) override {
        activeTetromino.tetromino.rotate90Clockwise();
        return activeTetromino;
    }
};

class BoardModel {
    static constexpr int numberColumns{12};
    static constexpr int numberRows{20};
    static constexpr int tetrominoQueueLength{3};

    TileGrid grid;
    TetrisScore score;

    ActiveTetromino activeTetromino;
    std::queue<ActiveTetromino> tetrominoQueue;

    TetrominoMoveRightStrategy *const moveRightStrategy = new TetrominoMoveRightStrategy();
    TetrominoMoveLeftStrategy *const moveLeftStrategy = new TetrominoMoveLeftStrategy();
    TetrominoMoveDownStrategy *const moveDownStrategy = new TetrominoMoveDownStrategy();
    TetrominoRotateStrategy *const rotateStrategy = new TetrominoRotateStrategy();


    TetrominoMoveStrategy *activeMoveStrategy;

    void moveActiveTetromino(TetrominoMoveStrategy *);

    void settleTetromino();

    bool checkTetrominoCollision() const;

    bool checkWallCollision() const;

    bool checkBottomCollision();

    void resetBoard();

    bool isRowComplete(std::vector<TileGridCell> &row) const;

    void fillTetrominoQueue();

public:
    BoardModel(): grid(numberRows, numberColumns), activeMoveStrategy(moveDownStrategy) {
        resetBoard();
    }

    void moveActiveTetrominoRight();

    void moveActiveTetrominoLeft();

    void moveActiveTetrominoDown();

    void rotateActiveTetromino();

    void spawnNextTetromino();

    const TileGrid &getTileGrid() const { return grid; }

    const ActiveTetromino &getActiveTetromino() const {
        return activeTetromino;
    }

    const std::queue<ActiveTetromino> &getTetrominoQueue() const {
        return tetrominoQueue;
    }

    const TetrisScore& getScore()const {return score;}

    int deleteCompleteRows();
};


#endif //BOARDMODEL_H
