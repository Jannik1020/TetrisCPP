//
// Created by jannikthiele on 28.04.25.
//

#ifndef TILEGRID_H
#define TILEGRID_H
#include <iostream>
#include <vector>

#include "SFML/Graphics/Color.hpp"


class Tile {
    sf::Color color;
public:
    Tile():color(sf::Color::White){}
    explicit Tile(sf::Color color): color(color){}

    sf::Color getColor() const {return color;}
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
    friend std::ostream &operator<<(std::ostream &os, const Grid<TileGridCell> &grid);

public:
    const int columns;
    const int rows;

    Grid(int rows, int columns): grid(rows, std::vector<T>(columns, T())),
                                     columns(columns),
                                     rows(rows) {
    }

    Grid(std::initializer_list<std::initializer_list<T>> init): columns(init.size()), rows(init.begin()->size()) {
        for (const auto& row : init) {
            grid.emplace_back(row);
        }
    }

    Grid(Grid const &otherGrid): grid(otherGrid.grid), columns(otherGrid.columns), rows(otherGrid.rows) {}

    void popRow(int row){grid.erase(grid.begin()+row);}
    void pushRow(std::vector<T> row) {grid.insert(grid.begin(), row);}
    void pushEmptyRow() {pushRow(std::vector<T>(columns, T()));}

    std::vector<T> &operator[](int idx) { return grid[idx]; }
    const std::vector<T> &operator[](int idx) const { return grid[idx]; }

    T & getCellAt (int row, int col) {return grid[row][col];}
    const T & getCellAt (int row, int col) const {return grid[row][col];}
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
