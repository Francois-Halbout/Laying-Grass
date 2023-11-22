// Board.h
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <unordered_map>
#include "Shape.h"

class Board {
public:
    Board(int gridSize);
    ~Board();

    void display() const;
    bool placeShape(const Shape1& shape, int playerNumber, int row, int col);
    void setPlayerColor(int playerNumber, char color);
    void setPlayerStartingPosition(int playerNumber, char color);

private:
    int gridSize;
    std::vector<std::vector<char>> board;
    std::unordered_map<int, char> playerColors;
    int playerToColor(int playerNumber) const;
    int lettreToColor(char lettre) const;
};

#endif // BOARD_H