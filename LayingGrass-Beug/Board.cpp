// Board.cpp
#include "Board.h"
#include "Shape.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <Windows.h>
#include <typeinfo>


Board::Board(int gridSize) : gridSize(gridSize) {
    board.resize(gridSize, std::vector<char>(gridSize, 0));
    boardPlayeur.resize(gridSize, std::vector<char>(gridSize, '0'));

    for (int i = 1; i <= 9; ++i) {
        char color = playerToColor(i);
        playerColors[i] = color;
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

            char cellPlayer = boardPlayeur[row - 1][col - 1];
            if (cellPlayer >= '1' && cellPlayer <= '9') {
                int playerNumber = cellPlayer - '0';
                char cellColor = playerColors.at(playerNumber);

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cellColor);
            }
            else {
                // R�initialiser la couleur � blanc par d�faut pour les cellules vides
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            char content = boardCode(cellContent);

            std::cout << content << "   ";
        }

        // R�initialiser la couleur apr�s avoir affich� une ligne
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << '\n';
    }

}

int Board::boardCode(int caseCode) const {
    // Vous pouvez d�finir la correspondance entre les num�ros de joueur et les num�ros de couleur ici
    switch (caseCode) {
    case 0: return '.'; // case vide
    case 1: return '#'; // case pleine
    case 2: return ' '; // mettre les icones des bonus
    case 3: return ' ';
    case 11: return '1'; // �a c'est pour le point de d�parts des joueurs
    case 12: return '2';
    case 13: return '3';
    case 14: return '4';
    case 15: return '5';
    case 16: return '6';
    case 17: return '7';
    case 18: return '8';
    case 19: return '9';
    default: return caseCode;  // Blanc par d�faut
    }
}

int Board::playerToColor(int playerNumber) const {
    // Vous pouvez d�finir la correspondance entre les num�ros de joueur et les num�ros de couleur ici
    switch (playerNumber) {
    case 1: return 4;  // Rouge
    case 2: return 1;  // Bleu
    case 3: return 2;  // Vert
    case 4: return 14; // Jaune (rouge + vert)
    case 5: return 6;  // Orange (rouge + vert)
    case 6: return 5;  // Violet (rouge + bleu)
    case 7: return 10;  // Cyan (vert + bleu)
    case 8: return 13; // fushia
    case 9: return 8; // Gris 
    default: return 15;  // Blanc par d�faut
    }
}

int Board::lettreToColor(char lettre) const {
    // Vous pouvez d�finir la correspondance entre les num�ros de joueur et les num�ros de couleur ici
    switch (lettre) {
    case 'R': return 4;  // Rouge
    case 'B': return 1;  // Bleu
    case 'V': return 2;  // Vert
    case 'J': return 14; // Jaune (rouge + vert)
    case 'O': return 6;  // Orange (rouge + vert)
    case 'M': return 5;  // Mauve (rouge + bleu)
    case 'C': return 10;  // Cyan (vert + bleu)
    case 'F': return 13; // fushia
    case 'G': return 8;  // Gris
    default: return 15;  // Blanc par d�faut
    }
}


void Board::setPlayerStartingPosition(int playerNumber, char color) {
    // Calculate the center of the player's square
    int centerX = (playerNumber - 1) % (gridSize / 10) * 10 + 5;
    int centerY = (playerNumber - 1) / (gridSize / 10) * 10 + 5;

    // Set the player's number in the center of their square
    char playerChar = '0' + static_cast<char>(playerNumber);
    boardPlayeur[centerY - 1][centerX - 1] = playerChar;
    board[centerY - 1][centerX - 1] = boardCode(10 + playerNumber);
}


void Board::setPlayerColor(int playerNumber, char color) {
    char playerColor = lettreToColor(color);
    playerColors.at(playerNumber) = playerColor;
}

bool Board::placeShape(const Shape1& shape, int playerNumber, int row, int col) {
    if (row < 1 || row + shape.getHeight() - 1 > gridSize || col < 1 || col + shape.getWidth() - 1 > gridSize) {
        return false;
    }

    for (size_t i = 0; i < shape.getHeight(); ++i) {
        for (size_t j = 0; j < shape.getWidth(); ++j) {
            if (shape.getCell(i, j) != ' ' && boardPlayeur[row - 1 + i][col - 1 + j] != '0') {
                return false;
            }
        }
    }

    for (size_t i = 0; i < shape.getHeight(); ++i) {
        for (size_t j = 0; j < shape.getWidth(); ++j) {
            if (shape.getCell(i, j) != ' ') {
                boardPlayeur[row - 1 + i][col - 1 + j] = '0' + playerNumber;
                board[row - 1 + i][col - 1 + j] = 1;
            }
        }
    }

    return true;
}
