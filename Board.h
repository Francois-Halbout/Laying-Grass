// Board.h

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Shape.h"

class Board {
public:
    Board(int gridSize);
    ~Board();

    void display() const;
    bool placeShape(const Shape1& shape, int playerNumber, int row, int col);

private:
    int gridSize;
    std::vector<std::vector<char>> board;
};

#endif // BOARD_H
