//
// Created by jannikthiele on 28.04.25.
//

#ifndef BOARDMODEL_H
#define BOARDMODEL_H
#include "Tetromino.h"
#include "TileGrid.h"

struct Position {
    int x;
    int y;

    Position():x(0),y(0){}
    Position(int x, int y): x(x), y(y) {
    }
};

struct ActiveTetromino {
    Tetromino tetromino;
    int x = 0;
    int y = 0;

    ActiveTetromino(const Tetromino &tetromino): tetromino(tetromino){}
    ActiveTetromino(ActiveTetromino const& other):tetromino(other.tetromino) {
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

class MoveStrategy {
public:
    virtual ~MoveStrategy() = default;

    virtual Position move(Position position) =0;
};

class MoveRightStrategy : public MoveStrategy {
public:
    Position move(Position position) override {
        position.x += 1;
        return position;
    }
};

class MoveLeftStrategy : public MoveStrategy {
    Position move(Position position) override {
        position.x -= 1;
        return position;
    }
};

class MoveDownStrategy : public MoveStrategy {
    Position move(Position position) override {
        position.y += 1;
        return position;
    }
};


class BoardModel {
    static constexpr int numberColumns{12};
    static constexpr int numberRows{20};

    TileGrid grid;

    Tetromino *activeTetromino;
    Position activeTetrominoPosition;


    MoveRightStrategy* const moveRightStrategy = new MoveRightStrategy();
    MoveLeftStrategy* const moveLeftStrategy = new MoveLeftStrategy();
    MoveDownStrategy* const moveDownStrategy= new MoveDownStrategy();

    MoveStrategy* activeMoveStrategy;

    void moveActiveTetromino(MoveStrategy* );

    void settleTetromino();

    bool checkTetrominoCollision() const;

    bool checkWallCollision() const;

    bool checkBottomCollision();

    void resetBoard();

    bool isRowComplete(std::vector<TileGridCell> &row) const;

public:
    BoardModel(): grid(numberRows, numberColumns), activeTetromino(nullptr), activeTetrominoPosition(0, 0), activeMoveStrategy(moveDownStrategy) {
        resetBoard();
    }

    void moveActiveTetrominoRight();

    void moveActiveTetrominoLeft();

    void moveActiveTetrominoDown();

    void rotateActiveTetromino();

    void spawnNewTetromino();

    const TileGrid & getTileGrid() {return grid;}
    const Tetromino* const& getActiveTetromino() const {
        return activeTetromino;
    }
    const Position & getActiveTetrominoPosition() const {
        return activeTetrominoPosition;
    }

    void deleteCompleteRows();
};


#endif //BOARDMODEL_H
