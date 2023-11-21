// Tile.cpp
#include "Tile.h"

Tile::Tile() : Shape1({ {'#', '#', '#'},
                       {'#', ' ', ' '},
                       {'#', ' ', ' '} }) {
}

Tile::Tile(const std::vector<std::vector<char>>& initialShape) : Shape1(initialShape) {
}

Tile::~Tile() {
}