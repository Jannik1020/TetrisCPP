//
// Created by jannikthiele on 28.04.25.
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include "BoardView.h"


class BoardController {
    BoardModel& boardModel;

public:
    BoardController(BoardModel& model) : boardModel(model) {}

    void moveTetrominoRight() const {
        boardModel.moveActiveTetrominoRight();
    }
    void moveTetrominoLeft() const {
        boardModel.moveActiveTetrominoLeft();
    }
    void moveTetrominoDown() const {
         boardModel.moveActiveTetrominoDown();
    }

    void deleteCompleteRows() {
        boardModel.deleteCompleteRows();
    }

    void rotateTetromino() {
        boardModel.rotateActiveTetromino();
    }
};



#endif //BOARDCONTROLLER_H
