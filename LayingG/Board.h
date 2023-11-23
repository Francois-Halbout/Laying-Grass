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

    int calculatePlayerScore(int playerNumber) const;  // Updated declaration
    int calculateGrassCount(int playerNumber, int row, int col, int squareSize) const;  // New declaration

private:
    int gridSize;
    std::vector<std::vector<char>> board;
    std::vector<std::vector<char>> boardPlayeur;
    std::unordered_map<int, char> playerColors;
    int playerToColor(int playerNumber) const;
    int lettreToColor(char lettre) const;
    int boardCode(int caseCode) const;
};

#endif // BOARD_H
