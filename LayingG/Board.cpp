// Board.cpp
#include "Board.h"
#include "Shape.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <Windows.h>


Board::Board(int gridSize) : gridSize(gridSize) {
    board.resize(gridSize, std::vector<char>(gridSize, ' '));

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

            // Convert the player number to color before setting the text attribute
            int playerColor = (cellContent >= '1' && cellContent <= '9') ? playerToColor(cellContent - '0') : 15;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), playerColor);

            std::cout << ((cellContent == ' ') ? '.' : cellContent) << "   ";

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }

        std::cout << '\n';
    }

}

int Board::playerToColor(int playerNumber) const {
    // Vous pouvez définir la correspondance entre les numéros de joueur et les numéros de couleur ici
    switch (playerNumber) {
    case 1: return 4;  // Rouge
    case 2: return 1;  // Bleu
    case 3: return 2;  // Vert
    case 4: return 14; // Jaune (rouge + vert)
    case 5: return 6;  // Orange (rouge + vert)
    case 6: return 5;  // Violet (rouge + bleu)
    case 7: return 3;  // Cyan (vert + bleu)
    case 8: return 7;  // Blanc (rouge + bleu + vert)
    case 9: return 10; // Vert (bleu + vert)
    default: return 15;  // Blanc par défaut
    }
}

void Board::setPlayerStartingPosition(int playerNumber, char color) {
    // Calculate the center of the player's square
    int centerX = (playerNumber - 1) % (gridSize / 10) * 10 + 5;
    int centerY = (playerNumber - 1) / (gridSize / 10) * 10 + 5;

    // Set the player's number in the center of their square
    char playerChar = '0' + static_cast<char>(playerNumber);
    board[centerY - 1][centerX - 1] = playerChar;
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
