#include <iostream>
#include <vector>
#include "Player.h"
#include "Shape.h"
#include "Board.h"
#include "Tile.h"
#include <algorithm>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cmath>


int main() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //Message de bienvenue
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
    std::string numPlayersChar;
    std::cout << "Enter the number of players (2 to 9): ";
    std::cin >> numPlayersChar;

    while (numPlayersChar.find_first_not_of("0123456789") != std::string::npos || std::stoi(numPlayersChar) < 2 || std::stoi(numPlayersChar) > 9) {
        std::cerr << "Invalid number of players. Exiting.\n";
        std::cout << "Enter the number of players (2 to 9): ";
        std::cin >> numPlayersChar;
    }
    const char COLORS[] = { 'R', 'B', 'V', 'J', 'O', 'M', 'C', 'F', 'G' };
    int numPlayers = std::stoi(numPlayersChar);

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

    for (const auto& player : players) {
        gameBoard.setPlayerStartingPosition(player.getNumber(), player.getColor());
    }
    gameBoard.display();

    // Initialisation des tuiles
    std::vector<Shape1> allTilesGame;

    Tile tiles;
    for (int i = 0; i < 98; ++i) {
        allTilesGame.push_back(Shape1(tiles.getShape(i)));
    }

    std::random_shuffle(allTilesGame.begin(), allTilesGame.end());
    int n = std::ceil(10.67 * numPlayers);
    std::vector<Shape1> allTiles(allTilesGame.begin(), allTilesGame.begin() + n);

    // Boucle de jeu
    int indexTile = 0;

    for (int round = 1; round <= 9; ++round) {
        std::cout << "Current round: " << round << "\n";

        for (auto& player : players) {
            std::cout << "Player " << player.getName() << ", it's your turn!\n";

            if (indexTile >= allTiles.size()) {
                indexTile = 0;
            }
            Shape1 currentTile = allTiles.at(indexTile); // round correspond à l'indice de la shape dans la liste alltiles
            
            if (currentTile.getWidth() != 0) {
                std::cout << "Current Tile:\n";
                currentTile.display();

                char displayChoice;

                do {
                    std::cout << "Display next 5 tiles (T), skip (S), display the board (D), or do nothing (N): ";
                    std::cin >> displayChoice;

                    if (displayChoice == 'T' || displayChoice == 't') {
                        player.displayNext5Tiles(indexTile, allTiles);
                    }
                    else if (displayChoice == 'D' || displayChoice == 'd') {
                        std::cout << "Current Board:\n";
                        gameBoard.display();
                    }
                    else if (displayChoice == 'S' || displayChoice == 's') {
                        if (player.haveSkip) {
                            int rep = 0;
                            while (1 > rep || rep > 5) {
                                player.displayNext5Tiles(indexTile, allTiles);
                                std::cout << "Which one do you want to exchange ?(1,2,3,4,5) : ";
                                std::cin >> rep;
                            }
                            indexTile = indexTile + rep;
                            currentTile = allTiles.at(indexTile);
                            player.haveSkip = false;
                        }
                        else {
                            std::cout << "You can't skip anymore (0 available)\n";
                        }
                    }
                } while (displayChoice != 'N' && displayChoice != 'n');

                std::cout << "Current tile:\n";
                currentTile.display();
                currentTile = player.manipulateTile(currentTile);

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
                if (indexTile >= allTiles.size()) {
                    indexTile = 0;
                }
                allTiles.erase(allTiles.begin() + indexTile);
            }
        }
    }
    //Boucle fin du jeu
    std::cout << "The game is over.\n";

    int maxScore = -1;
    std::vector<int> liste_winner = { -1 };

    for (auto& player : players) {
        int playerScore = gameBoard.calculatePlayerScore(player.getNumber());
        std::cout << "Player " << player.getName() << " score: " << playerScore << '\n';
        if (playerScore > maxScore) {
            maxScore = playerScore;
            liste_winner = { player.getNumber() };
        }
        else if (playerScore == maxScore){
            liste_winner.push_back(player.getNumber());
        }
    }

    int maxgrass = -1;
    int winner = -1;
    if (liste_winner.size() > 1) {
        for (int joueur = 0; joueur <= liste_winner.size(); joueur++) {
            int grassjoueur = gameBoard.calculateGrass(liste_winner[joueur]);
            if (maxgrass < grassjoueur) {
                maxgrass = grassjoueur;
                winner = liste_winner[joueur];
            }
        }
        std::cout << "The winner is \"" << players.at(winner).getName() << "\"!\n";
    }
    else {
        std::cout << "The winner is \"" << players.at(liste_winner.at(0)).getName() << "\"!\n";
    }
    return 0;
}
