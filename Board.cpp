// Board.cpp

#include "Board.h"
#include "Shape.h"
#include <iostream>
#include <cstdlib> // Ajoutez cet en-tête pour srand et rand

Board::Board(int gridSize) : gridSize(gridSize) {
    // Initialize the board with empty spaces
    board.resize(gridSize, std::vector<char>(gridSize, ' '));

    // Initialize player colors (default is '.')
    for (int i = 1; i <= 9; ++i) {
        playerColors[i] = '#';
    }
}

Board::~Board() {}

void Board::display() const {
    // Display the column headers
    std::cout << "   ";
    for (int col = 1; col <= gridSize; ++col) {
        if (col < 10) {
            std::cout << col << "   "; // Adjust spacing for single-digit column numbers
        }
        else {
            std::cout << col << "  ";  // Adjust spacing for double-digit column numbers
        }
    }
    std::cout << '\n';

    for (int row = 1; row <= gridSize; ++row) {
        // Display the row header
        if (row < 10) {
            std::cout << row << "  "; // Adjust spacing for single-digit row numbers
        }
        else {
            std::cout << row << " ";  // Adjust spacing for double-digit row numbers
        }

        for (int col = 1; col <= gridSize; ++col) {
            // Display the content of each cell on the board
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
    // Check if the placement is within the board boundaries
    if (row < 1 || row + shape.getShape().size() - 1 > gridSize || col < 1 || col + shape.getShape()[0].size() - 1 > gridSize) {
        return false;
    }

    // Check if the placement is on an empty cell
    for (size_t i = 0; i < shape.getShape().size(); ++i) {
        for (size_t j = 0; j < shape.getShape()[i].size(); ++j) {
            if (shape.getShape()[i][j] != ' ' && board[row - 1 + i][col - 1 + j] != ' ') {
                return false;
            }
        }
    }

    // Place the shape on the board
    for (size_t i = 0; i < shape.getShape().size(); ++i) {
        for (size_t j = 0; j < shape.getShape()[i].size(); ++j) {
            if (shape.getShape()[i][j] != ' ') {
                // Set the cell to the player's color
                board[row - 1 + i][col - 1 + j] = playerColors[playerNumber];
            }
        }
    }

    return true;
}



