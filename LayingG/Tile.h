// Tile.h
#include <vector>
#ifndef TILE_H
#define TILE_H


class Tile {
public:
    Tile();
    ~Tile();
    std::vector<std::vector<char>> getShape(int shapeIndex);

private:
    std::vector<std::vector<char>> currentShape;
};

#endif // TILE_H
