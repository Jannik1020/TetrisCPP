//
// Created by jannikthiele on 28.04.25.
//

#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>

#include "TileGrid.h"

namespace TetrominoShape {
    using TetrominoShapeGrid = Grid<bool>;
    inline constexpr TetrominoShapeGrid J_SHAPE = {
        {
            {false, true, false},
            {false, true, false},
            {true, true, false}
        }
    };

    inline constexpr TetrominoShapeGrid L_SHAPE = {
        {
            {false, true, false},
            {false, true, false},
            {false, true, true}
        }
    };

    inline constexpr TetrominoShapeGrid S_SHAPE = {
        {
            {false, false, false},
            {false, true, true},
            {true, true, false}
        }
    };
    inline constexpr TetrominoShapeGrid Z_SHAPE = {
        {
            {false, false, false},
            {true, true, false},
            {false, true, true}
        }
    };
    inline constexpr TetrominoShapeGrid T_SHAPE = {
        {
            {false, false, false},
            {true, true, true},
            {false, true, false}
        }
    };
    inline constexpr TetrominoShapeGrid I_SHAPE = {
        {
            {false, false, false, false},
            {false, false, false, false},
            {true, true, true, true },
            {false, false, false, false}
        }
    };
    inline constexpr TetrominoShapeGrid SQR_SHAPE = {
        {
            {false, false, false, false},
            {false, true, true, false},
            {false, true, true, false },
            {false, false, false, false}
        }
    };
    inline constexpr std::array<TetrominoShapeGrid, 7> Shapes = {J_SHAPE, L_SHAPE, S_SHAPE, Z_SHAPE, T_SHAPE, I_SHAPE, SQR_SHAPE};
};

class Tetromino {
    TileGrid grid;
    sf::Color color;

public:
    Tetromino(TetrominoShape::TetrominoShapeGrid& shape, sf::Color color);
    int getBoundingSize() const{return grid.columns;}
    TileGrid const & getTileGrid(){return grid;}
};


#endif //TETROMINO_H
