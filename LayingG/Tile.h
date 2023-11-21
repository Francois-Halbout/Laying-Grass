// Tile.h
#ifndef TILE_H
#define TILE_H

#include "Shape.h"

class Tile : public Shape1 {
public:
    Tile();
    Tile(const std::vector<std::vector<char>>& initialShape);
    ~Tile();
};

#endif // TILE_H