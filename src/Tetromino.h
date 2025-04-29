//
// Created by jannikthiele on 28.04.25.
//

#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>

#include "TileGrid.h"


namespace TetrominoShape {
    using TetrominoShapeGrid = Grid<int>;
    static const TetrominoShapeGrid J_SHAPE = {
        { {false, true, false},
          {false, true, false},
          {true, true, false} }
    };

    static const TetrominoShapeGrid L_SHAPE = {
        { {false, true, false},
          {false, true, false},
          {false, true, true} }
    };

    static const TetrominoShapeGrid S_SHAPE = {
        { {false, false, false},
          {false, true, true},
          {true, true, false} }
    };

    static const TetrominoShapeGrid Z_SHAPE = {
        { {false, false, false},
          {true, true, false},
          {false, true, true} }
    };

    static const TetrominoShapeGrid T_SHAPE = {
        { {false, false, false},
          {true, true, true},
          {false, true, false} }
    };

    static const TetrominoShapeGrid I_SHAPE = {
        { {false, false, false, false},
          {false, false, false, false},
          {true, true, true, true},
          {false, false, false, false} }
    };

    static const TetrominoShapeGrid SQR_SHAPE = {
        { {false, false, false, false},
          {false, true, true, false},
          {false, true, true, false},
          {false, false, false, false} }
    };

    static const std::array<TetrominoShapeGrid, 7> Shapes = {J_SHAPE, L_SHAPE, S_SHAPE, Z_SHAPE, T_SHAPE, I_SHAPE, SQR_SHAPE};
    static const std::array<sf::Color, 7> ShapeColors = {sf::Color::Yellow, sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta, sf::Color::White};

}
class Tetromino {
    TileGrid grid;
    sf::Color color;

public:
    Tetromino(const TetrominoShape::TetrominoShapeGrid& shape, sf::Color color);
    int getBoundingSize() const{return grid.columns;}
    int getFirstOccupiedGridRow();
    int getLastOccupiedGridRow();
    int getFirstOccupiedGridColumn();
    int getLastOccupiedGridColumn();
    void rotate90Clockwise() ;
    TileGrid const & getTileGrid()const {return grid;}
};


#endif //TETROMINO_H
