#include <iostream>
#include <vector>
#include "Player.h"
#include "Board.h"
#include "Tile.h"  // Ajout de l'inclusion de Tile.h
#include <algorithm>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Display welcome message
    std::cout << R"(
				      _______        _______   ______               ______   ______
|	  /\     \   /   |   |\   |  |              |         |      |      /\     |        |
|	 /__\	  \ /    |   | \  |  |    ___       |    ___  |______|     /__\    |______  |______
|	/    \     |     |   |  \ |  |       |      |       | |      \    /    \          |        |
|_____ /      \    |     |   |   \|  |_______|      |_______| |       \  /      \  _______| _______|
)" << "\n";

    char playGame;
    std::cout << "Hello! Welcome to Laying Grass. Do you want to play? (Y/N): ";
    std::cin >> playGame;

    if (playGame != 'Y' && playGame != 'y') {
        std::cout << "Goodbye! Thanks for considering. Exiting.\n";
        return 0;
    }
    // Initialisation des joueurs
    std::vector<Player> players;
    int numPlayers;

    std::cout << "Enter the number of players (2 to 9): ";
    std::cin >> numPlayers;

    const char COLORS[] = { 'R', 'B', 'V', 'J', 'O', 'M', 'C', 'F', 'G' };

    if (numPlayers < 2 || numPlayers > 9) {
        std::cerr << "Invalid number of players. Exiting.\n";
        return 1;
    }


    // Initialisation du plateau
    int gridSize = (numPlayers <= 4) ? 20 : 30;
    Board gameBoard(gridSize);

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
        while (colorIt == std::end(COLORS)) {
            std::cerr << "Invalid color. Exiting.\n";
            std::cout << "Enter color for Player " << i + 1 << " (";
            for (const char& color : COLORS) {
                std::cout << color << ' ';
            }

            std::cout << "): ";
            std::cin >> playerColor;
            colorIt = std::find(std::begin(COLORS), std::end(COLORS), playerColor);
        }

        player.setColor(playerColor);
        gameBoard.setPlayerColor(i + 1, playerColor);
        player.giveStartingTile();
        player.giveTileExchangeCoupon();

        player.setNumber(i + 1);

        players.push_back(player);
    }


    // Set starting positions for each player
    for (const auto& player : players) {
        gameBoard.setPlayerStartingPosition(player.getNumber(), player.getColor());
    }

    gameBoard.display();


    // Initialisation des tuiles
    std::vector<Tile> allTiles;
    for (int i = 0; i < 96; ++i) {
        Tile tile;
        allTiles.push_back(tile);
    }

    std::random_shuffle(allTiles.begin(), allTiles.end());

    // Boucle de jeu
    // ...
// Inside the game loop
    for (int round = 1; round <= 9; ++round) {
        std::cout << "Current round: " << round << "\n";

        for (auto& player : players) {
            std::cout << "Player " << player.getName() << ", it's your turn!\n";

            if (!allTiles.empty()) {
                // Display the current tile's shape
                std::cout << "Current Tile:\n";
                allTiles.back().display();

                // Ask the player to manipulate and place the tile
                player.displayNextTiles();  // Display the next tiles
                allTiles = player.manipulateTile(allTiles);  // Allow the player to manipulate the tile

                int row, col;

                while (true) {
                    std::cout << "Enter the row and column to place the tile : ";
                    std::cin >> row >> col;

                    if (gameBoard.placeShape(allTiles.back(), player.getNumber(), row, col) && player.canPlaceTile(allTiles.back())) {
                        break;
                    }
                    else {
                        std::cout << "Invalid move. Try again.\n";
                    }
                }

                std::cout << "Current Board:\n";
                gameBoard.display();
                std::cout << std::endl;

                // Remove the placed tile from the list
                allTiles.pop_back();
            }
        }
    }
    // After the 9 rounds
    std::cout << "The game is over.\n";

    int maxScore = -1;
    Player winner;

    for (auto& player : players) {
        int playerScore = gameBoard.calculatePlayerScore(player.getNumber());
        std::cout << "Player " << player.getName() << " score: " << playerScore << '\n';

        if (playerScore > maxScore || (playerScore == maxScore && playerScore > winner.getNumber())) {
            maxScore = playerScore;
            winner = player;
        }
    }

    std::cout << "The winner is \"" << winner.getName() << "\"!\n";





    return 0;
}
