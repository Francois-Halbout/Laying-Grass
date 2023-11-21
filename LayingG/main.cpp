#include <iostream>
#include <vector>
#include "Player.h"
#include "Board.h"
#include "Tile.h"  // Ajout de l'inclusion de Tile.h
#include <algorithm>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialisation des joueurs
    std::vector<Player> players;
    int numPlayers;

    std::cout << "Enter the number of players (2 to 9): ";
    std::cin >> numPlayers;

    const char COLORS[] = { 'R', 'B', 'G', 'Y', 'O', 'P', 'C', 'M', 'V' };

    if (numPlayers < 2 || numPlayers > 9) {
        std::cerr << "Invalid number of players. Exiting.\n";
        return 1;
    }

    for (int i = 0; i < numPlayers; ++i) {
        Player player;
        std::string playerName;
        char playerColor;

        std::cout << "Enter name for Player " << i + 1 << ": ";
        std::cin >> playerName;
        player.setName(playerName);

        std::cout << "Enter color for Player " << i + 1 << " (";
        for (const char& color : COLORS) {
            std::cout << color << ' ';
        }
        std::cout << "): ";
        std::cin >> playerColor;

        auto colorIt = std::find(std::begin(COLORS), std::end(COLORS), playerColor);
        if (colorIt == std::end(COLORS)) {
            std::cerr << "Invalid color. Exiting.\n";
            return 1;
        }

        player.setColor(playerColor);
        player.giveStartingTile();
        player.giveTileExchangeCoupon();

        player.setNumber(i + 1);

        players.push_back(player);
    }

    // Initialisation du plateau
    int gridSize = (numPlayers <= 4) ? 20 : 30;
    Board gameBoard(gridSize);

    // Initialisation des tuiles
    std::vector<Tile> allTiles;
    for (int i = 0; i < 96; ++i) {
        Tile tile;
        allTiles.push_back(tile);
    }

    std::random_shuffle(allTiles.begin(), allTiles.end());

    // Boucle de jeu
    for (int round = 1; round <= 9; ++round) {
        std::cout << "Current round: " << round << "\n";

        for (auto& player : players) {
            std::cout << "Player " << player.getName() << ", it's your turn!\n";

            if (!allTiles.empty()) {
                // Demandez au joueur de manipuler et placer sa tuile
                Tile currentTile = allTiles.back();
                allTiles.pop_back();

                player.displayNextTiles();  // Afficher les tuiles suivantes
                player.manipulateTile(currentTile);  // Permettre au joueur de manipuler la tuile

                int row, col;

                while (true) {
                    std::cout << "Enter the row and column to place the tile : ";
                    std::cin >> row >> col;

                    if (gameBoard.placeShape(currentTile, player.getNumber(), row, col) && player.canPlaceTile(currentTile)) {
                        break;
                    }
                    else {
                        std::cout << "Invalid move. Try again.\n";
                    }
                }

                std::cout << "Current Board:\n";
                gameBoard.display();
                std::cout << std::endl;
            }
        }
    }

    return 0;
}
