// Board.cpp

#include "Board.h"
#include <iostream>

Board::Board(int gridSize) : gridSize(gridSize) {
    // Initialize the board with empty spaces
    board.resize(gridSize, std::vector<char>(gridSize, ' '));
}

Board::~Board() {}

void Board::display() const {
    // Display the current state of the board
    for (const auto& row : board) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}

bool Board::placeShape(const Shape1& shape, int playerNumber, int row, int col) {
    // Place the shape on the board if it's a valid move
    const auto& shapeData = shape.getShape();

    // Check if the placement is within bounds
    if (row < 0 || col < 0 || row + shapeData.size() > gridSize || col + shapeData[0].size() > gridSize) {
        std::cout << "Invalid placement. Out of bounds.\n";
        return false;
    }

    // Check if the placement collides with existing shapes
    for (size_t i = 0; i < shapeData.size(); ++i) {
        for (size_t j = 0; j < shapeData[i].size(); ++j) {
            if (shapeData[i][j] != ' ' && board[row + i][col + j] != ' ') {
                std::cout << "Invalid placement. Collision with existing shape.\n";
                return false;
            }
        }
    }

    // Place the shape on the board
    for (size_t i = 0; i < shapeData.size(); ++i) {
        for (size_t j = 0; j < shapeData[i].size(); ++j) {
            if (shapeData[i][j] != ' ') {
                board[row + i][col + j] = shapeData[i][j];
            }
        }
    }

    // Print the updated board
    display();

    return true;
}
