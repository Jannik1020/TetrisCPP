//
// Created by jannikthiele on 28.04.25.
//

#ifndef TILEGRID_H
#define TILEGRID_H
#include <vector>

#include "SFML/Graphics/Color.hpp"


class Tile {
    sf::Color color;
public:
    Tile():color(sf::Color::White){}
    explicit Tile(sf::Color color): color(color){}

    sf::Color getColor() {return color;}
};

class TileGridCell {
    Tile *tile;
    bool isOccupied;

public:
    TileGridCell(): tile(nullptr), isOccupied(false) {
    }

    void attachTile(Tile *tile);
    void detachTile() ;

    void transferTile(TileGridCell & cell) ;

    bool isCellOccupied() const {return isOccupied;}
    const Tile*  getTile() const {return tile;}
};

template<typename T> class Grid {
    std::vector<std::vector<T>> grid;

public:
    const int columns;
    const int rows;

    Grid(int rows, int columns): grid(rows, std::vector<T>(columns, T())),
                                     columns(columns),
                                     rows(rows) {
    }

    Grid(std::initializer_list<std::initializer_list<T>> init): columns(init[0].size()), rows(init.size()) {
        for (const auto& row : init) {
            grid.emplace_back(row);
        }
    }

    std::vector<T> &operator[](int idx) { return grid[idx]; }
    const std::vector<T> &operator[](int idx) const { return grid[idx]; }

    T & getCellAt (int row, int col) {return grid[row][col];}
};

using TileGrid = Grid<TileGridCell>;

// class TileGrid {
//     std::vector<std::vector<TileGridCell>> grid;
//
// public:
//     const int columns;
//     const int rows;
//
//     TileGrid(int rows, int columns): grid(rows, std::vector<TileGridCell>(columns, TileGridCell())),
//                                      columns(columns),
//                                      rows(rows) {
//     }
//
//     std::vector<TileGridCell> &operator[](int idx) { return grid[idx]; }
//     const std::vector<TileGridCell> &operator[](int idx) const { return grid[idx]; }
//
//     TileGridCell & getCellAt (int row, int col) {return grid[row][col];}
// };

#endif //TILEGRID_H
