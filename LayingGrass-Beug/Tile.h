// Tile.h
#ifndef TILE_H
#define TILE_H

#include "Shape.h"
#include <string>

class Tile : public Shape1 {
public:
    Tile();  // Constructor for loading a random tile from file
    ~Tile();
};

#endif // TILE_H
