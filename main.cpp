// main.cpp

#include <iostream>
#include <vector>
#include "Player.h"
#include "Shape.h"
#include "Board.h"
#include <algorithm>
#include <ctime> // Include for std::time and std::srand

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for std::rand()

    // Initialize players
    std::vector<Player> players;
    int numPlayers;

    std::cout << "Enter the number of players (2 to 9): ";
    std::cin >> numPlayers;

    if (numPlayers < 2 || numPlayers > 9) {
        std::cerr << "Invalid number of players. Exiting.\n";
        return 1;
    }

    // Create players
    for (int i = 0; i < numPlayers; ++i) {
        Player player;
        std::string playerName;
        std::string playerColor;

        std::cout << "Enter name for Player " << i + 1 << ": ";
        std::cin >> playerName;
        player.setName(playerName);

        std::cout << "Enter color for Player " << i + 1 << ": ";
        std::cin >> playerColor;
        player.setColor(playerColor);

        player.giveStartingTile();
        player.giveTileExchangeCoupon();

        // Set the player number
        player.setNumber(i + 1);

        players.push_back(player);
    }

    // Initialize the board
    int gridSize = (numPlayers <= 4) ? 20 : 30;
    Board gameBoard(gridSize);

    // Randomly shuffle the player order
    std::random_shuffle(players.begin(), players.end());

    // Assuming allShapes is a vector containing shapes
    std::vector<Shape1> allShapes;  // Make sure to populate this vector with shapes

    // Populate allShapes with some shapes (example: 3 shapes)
    for (int i = 0; i < 3; ++i) {
        Shape1 shape;  // Assuming Shape1 has a default constructor
        allShapes.push_back(shape);
    }

    // Gameplay loop
    for (int round = 1; round <= 2; ++round) {
        std::cout << "\nRound " << round << " starts!\n";

        for (auto& player : players) {
            std::cout << "Player " << player.getName() << ", it's your turn!\n";

            // Display the current board
            std::cout << "Current Board:\n";
            gameBoard.display();

            // Check if allShapes is not empty before accessing back()
            if (!allShapes.empty()) {
                // Ask the player to place their shape
                Shape1 currentShape = allShapes.back(); // Assuming allShapes is a vector containing shapes

                int row, col;
                std::cout << "Enter the row and column to place the shape (e.g., 2 3): ";
                std::cin >> row >> col;

                // Keep asking until the player makes a valid move
                while (!gameBoard.placeShape(currentShape, player.getNumber(), row, col)) {
                    std::cout << "Try again.\n";
                    std::cout << "Enter the row and column to place the shape (e.g., 2 3): ";
                    std::cin >> row >> col;
                }

                // Remove the placed shape from allShapes
                allShapes.pop_back();
            }

            // ... (Continue with the rest of the gameplay logic)
        }
    }


    return 0;
}
