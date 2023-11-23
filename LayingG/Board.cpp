// Board.cpp
#include "Board.h"
#include "Shape.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <Windows.h>
#include <typeinfo>


// Inside the Board class implementation in board.cpp
Board::Board(int gridSize) : gridSize(gridSize) {
    board.resize(gridSize, std::vector<char>(gridSize, 0));
    boardPlayeur.resize(gridSize, std::vector<char>(gridSize, 0));

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
            std::cout << " " << col << " "; // Adjust spacing for single-digit column numbers
        }
        else {
            std::cout << col << " ";  // Adjust spacing for double-digit column numbers
        }
    }
    std::cout << '\n';

    for (int row = 1; row <= gridSize; ++row) {
        // Display the row header
        if (row < 10) {
            std::cout << " " << row << " "; // Adjust spacing for single-digit row numbers
        }
        else {
            std::cout << row << " ";  // Adjust spacing for double-digit row numbers
        }

        for (int col = 1; col <= gridSize; ++col) {
            // Display the content of each cell on the board
            char cellContent = board[row - 1][col - 1];

            int cellPlayer = boardPlayeur[row - 1][col - 1];
            if (cellPlayer >= 1 && cellPlayer <= 9) {
                char cellColor = playerColors.at(cellPlayer);

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cellColor);
            }
            else {
                // Réinitialiser la couleur à blanc par défaut pour les cellules vides
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            char content = boardCode(cellContent);

            if (cellContent == 1) {
                std::cout << content << content << " ";
            }
            else {
                std::cout << " " << content << " ";
            }
        }

        // Réinitialiser la couleur après avoir affiché une ligne
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << '\n';
    }

}

char Board::boardCode(int caseCode) const {
    // Vous pouvez définir la correspondance entre les numéros de joueur et les numéros de couleur ici
    switch (caseCode) {
    case 0: return 240; // case vide
    case 1: return 219; // case pleine
    case 2: return ' '; // mettre les icones des bonus
    case 3: return ' ';
    case 11: return '1'; // ça c'est pour le point de départs des joueurs
    case 12: return '2';
    case 13: return '3';
    case 14: return '4';
    case 15: return '5';
    case 16: return '6';
    case 17: return '7';
    case 18: return '8';
    case 19: return '9';
    default: return caseCode;  // Blanc par défaut
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
    case 6: return 5;  // Mauve (rouge + bleu)
    case 7: return 11;  // Cyan (vert + bleu)
    case 8: return 13; // fushia
    case 9: return 8; // Gris 
    default: return 15;  // Blanc par défaut
    }
}

int Board::lettreToColor(char lettre) const {
    // Vous pouvez définir la correspondance entre les numéros de joueur et les numéros de couleur ici
    switch (lettre) {
    case 'R': return 4;  // Rouge
    case 'B': return 1;  // Bleu
    case 'V': return 2;  // Vert
    case 'J': return 14; // Jaune (rouge + vert)
    case 'O': return 6;  // Orange (rouge + vert)
    case 'M': return 5;  // Mauve (rouge + bleu)
    case 'C': return 11;  // Cyan (vert + bleu)
    case 'F': return 13; // fushia
    case 'G': return 8;  // Gris
    default: return 15;  // Blanc par défaut
    }
}


void Board::setPlayerStartingPosition(int playerNumber, char color) {
    // Calculate the center of the player's square
    int centerX = (playerNumber - 1) % (gridSize / 10) * 10 + 5;
    int centerY = (playerNumber - 1) / (gridSize / 10) * 10 + 5;

    // Set the player's number in the center of their square
    boardPlayeur[centerY - 1][centerX - 1] = playerNumber;
    board[centerY - 1][centerX - 1] = boardCode(10 + playerNumber);
}


void Board::setPlayerColor(int playerNumber, char color) {
    char playerColor = lettreToColor(color);
    playerColors.at(playerNumber) = playerColor;
}

bool Board::placeShape(const Shape1& shape, int playerNumber, int row, int col) {
    if (row < 1 || row + shape.getHeight() >= gridSize +1 || col < 1 || col + shape.getWidth() >= gridSize + 1) {
        return false;
    }

    for (size_t i = 0; i < shape.getHeight(); ++i) {
        for (size_t j = 0; j < shape.getWidth(); ++j) {
            if (shape.getCell(i, j) != ' ' && board[row - 1 + i][col - 1 + j] != 0) {
                return false;
            }
        }
    }

    // condition d'arrêt si il y a un ennemi collé
    for (size_t i = 0; i < shape.getHeight(); ++i) {
        for (size_t j = 0; j < shape.getWidth(); ++j) {
            if (shape.getCell(i, j) != ' ') {
                // Vérifier que l'index n'est pas négatif et ne dépasse pas les limites du tableau
                if (row - 1 + i > 0) {
                    if (boardPlayeur[row - 1 + i - 1][col - 1 + j] != playerNumber && boardPlayeur[row - 1 + i - 1][col - 1 + j] != 0 && (1 <= boardPlayeur[row - 1 + i - 1][col - 1 + j] && boardPlayeur[row - 1 + i - 1][col - 1 + j] <= 9)) {
                        return false;
                    }
                }
                if (row - 1 + i < gridSize - 1) {
                    if (boardPlayeur[row - 1 + i + 1][col - 1 + j] != playerNumber && boardPlayeur[row - 1 + i + 1][col - 1 + j] != 0 && (1 <= boardPlayeur[row - 1 + i + 1][col - 1 + j] && boardPlayeur[row - 1 + i + 1][col - 1 + j] <= 9)) {
                        return false;
                    }
                }
                if (col - 1 + j > 0) {
                    if (boardPlayeur[row - 1 + i][col - 1 + j - 1] != playerNumber && boardPlayeur[row - 1 + i][col - 1 + j - 1] != 0 && (1 <= boardPlayeur[row - 1 + i][col - 1 + j - 1] && boardPlayeur[row - 1 + i][col - 1 + j - 1] <= 9)) {
                        return false;
                    }
                }
                if (col - 1 + j < gridSize - 1) {
                    if (boardPlayeur[row - 1 + i][col - 1 + j + 1] != playerNumber && boardPlayeur[row - 1 + i][col - 1 + j + 1] != 0 && (1 <= boardPlayeur[row - 1 + i][col - 1 + j + 1] && boardPlayeur[row - 1 + i][col - 1 + j + 1] <= 9)) {
                        return false;
                    }
                }
            }
        }
    }

    // condition d'arrêt si il n'y a pas de carré du joueur collé
    bool state = true;
    for (size_t i = 0; i != shape.getHeight(); ++i) {
        for (size_t j = 0; j != shape.getWidth(); ++j) {
            if (shape.getCell(i, j) != ' ') {
                // Vérifier que l'index n'est pas négatif avant d'acceder au board
                if (row - 1 + i > 0 && row - 1 + i < gridSize && col - 1 + j > 0 && col - 1 + j < gridSize) {
                    if (boardPlayeur[row - 2 + i][col - 1 + j] == playerNumber ||
                        boardPlayeur[row - 1 + i][col - 2 + j] == playerNumber ||
                        boardPlayeur[row - 1 + i][col + j] == playerNumber ||
                        boardPlayeur[row + i][col - 1 + j] == playerNumber) {
                        state = false;
                        break;
                    }
                }
            }
        }
    }

    if (state) {
        return false;
    }

    for (size_t i = 0; i < shape.getHeight(); ++i) {
        for (size_t j = 0; j < shape.getWidth(); ++j) {
            if (shape.getCell(i, j) != ' ') {
                boardPlayeur[row - 1 + i][col - 1 + j] = playerNumber;
                board[row - 1 + i][col - 1 + j] = 1;
            }
        }
    }

    return true;
}


int Board::calculateGrass(int playerNumber) {

    int grassCount = 0;

    for (int i = 0; i < boardPlayeur.size(); ++i) {
        for (int j = 0; j < boardPlayeur[0].size(); ++j) {
            if (boardPlayeur[i][j] == playerNumber) {
                grassCount++;
            }
        }
    }

    return grassCount;
}

int Board::calculatePlayerScore(int playerNumber) const {
    int maxCarre = 0;
    int lignes = boardPlayeur.size();
    int colonnes = boardPlayeur[0].size();

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            if (boardPlayeur[i][j] == playerNumber) {
                int carre = 1;

                while (i + carre < lignes && j + carre < colonnes) {
                    bool ligneOk = true;
                    bool colonneOk = true;

                    for (int x = i; x <= i + carre; ++x) {
                        if (boardPlayeur[x][j + carre] != playerNumber) {
                            ligneOk = false;
                            break;
                        }
                    }

                    for (int y = j; y <= j + carre; ++y) {
                        if (boardPlayeur[i + carre][y] != playerNumber) {
                            colonneOk = false;
                            break;
                        }
                    }

                    if (ligneOk && colonneOk) {
                        carre++;
                    }
                    else {
                        break;
                    }
                }

                maxCarre = max(maxCarre, carre);
            }
        }
    }

    return maxCarre;
}





