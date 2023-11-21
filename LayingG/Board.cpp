// Board.cpp
#include "Board.h"
#include "Shape.h"
#include <iostream>
#include <cstdlib>

Board::Board(int gridSize) : gridSize(gridSize) {
    board.resize(gridSize, std::vector<char>(gridSize, ' '));

    for (int i = 1; i <= 9; ++i) {
        playerColors[i] = '#';
    }
}

Board::~Board() {}

void Board::display() const {
    std::cout << "   ";
    for (int col = 1; col <= gridSize; ++col) {
        std::cout << col << "   ";
    }
    std::cout << '\n';

    for (int row = 1; row <= gridSize; ++row) {
        if (row < 10) {
            std::cout << row << "  ";
        }
        else {
            std::cout << row << " ";
        }

        for (int col = 1; col <= gridSize; ++col) {
            char cellContent = board[row - 1][col - 1];
            std::cout << ((cellContent == ' ') ? '.' : cellContent) << "   ";
        }

        std::cout << '\n';
    }
}

void Board::setPlayerColor(int playerNumber, char color) {
    playerColors[playerNumber] = color;
}

bool Board::placeShape(const Shape1& shape, int playerNumber, int row, int col) {
    if (row < 1 || row + shape.getHeight() - 1 > gridSize || col < 1 || col + shape.getWidth() - 1 > gridSize) {
        return false;
    }

    for (size_t i = 0; i < shape.getHeight(); ++i) {
        for (size_t j = 0; j < shape.getWidth(); ++j) {
            if (shape.getCell(i, j) != ' ' && board[row - 1 + i][col - 1 + j] != ' ') {
                return false;
            }
        }
    }

    for (size_t i = 0; i < shape.getHeight(); ++i) {
        for (size_t j = 0; j < shape.getWidth(); ++j) {
            if (shape.getCell(i, j) != ' ') {
                board[row - 1 + i][col - 1 + j] = playerColors[playerNumber];
            }
        }
    }

    return true;
}
