// Board.cpp
#include "Board.h"
#include "Shape.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>


Board::Board(int gridSize) : gridSize(gridSize) {
    board.resize(gridSize, std::vector<char>(gridSize, ' '));

    for (int i = 1; i <= 9; ++i) {
        playerColors[i] = '#';
    }
}

Board::~Board() {}


void Board::display() const {
    // Afficher les en-têtes de colonne avec une largeur fixe
    std::cout << std::setw(4) << "";  // Pour l'espace avant la première colonne
    for (int col = 1; col <= gridSize; ++col) {
        std::cout << std::setw(4) << col;
    }
    std::cout << '\n';

    for (int row = 1; row <= gridSize; ++row) {
        // Afficher les en-têtes de ligne avec une largeur fixe
        std::cout << std::setw(4) << row;

        for (int col = 1; col <= gridSize; ++col) {
            // Afficher le contenu de chaque cellule avec une largeur fixe
            char cellContent = board[row - 1][col - 1];
            std::cout << std::setw(4) << ((cellContent == ' ') ? '.' : cellContent);
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
