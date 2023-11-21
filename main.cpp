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

    const char COLORS[] = { 
        'R',
        'B',
        'G', 
        'Y',
        'O',
        'P',
        'C', 
        'M', 
        'V' };

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

        // Vérifiez si la couleur saisie est dans le tableau COLORS
        auto colorIt = std::find(std::begin(COLORS), std::end(COLORS), playerColor);
        if (colorIt == std::end(COLORS)) {
            std::cerr << "Invalid color. Exiting.\n";
            return 1;
        }

        player.setColor(playerColor);
        player.giveStartingTile();
        player.giveTileExchangeCoupon();

        // Définir le numéro du joueur
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
    for (int round = 1; round <= 9; ++round) {  // Update the number of rounds
        std::cout << "Current round: " << round << "\n";

        for (auto& player : players) {
            std::cout << "Player " << player.getName() << ", it's your turn!\n";

            // Check if allShapes is not empty before accessing back()
            if (!allShapes.empty()) {
                // Ask the player to place their shape
                Shape1 currentShape = allShapes.back();

                if (player.getShapeExchangeCoupons() > 0) {
                    std::cout << "Do you want to use a shape exchange coupon? (1 for Yes, 0 for No): ";
                    int useCoupon;
                    std::cin >> useCoupon;

                    if (useCoupon == 1) {
                        player.useShapeExchangeCoupon();

                        // Display the next five shapes
                        std::cout << "Next five shapes:\n";
                        for (size_t i = 0; i < 5 && i < allShapes.size(); ++i) {
                            allShapes[i].display();
                        }

                        // Ask the player to choose a shape
                        int shapeChoice;
                        std::cout << "Choose a shape (1 to 5): ";
                        std::cin >> shapeChoice;

                        if (shapeChoice >= 1 && shapeChoice <= 5) {
                            currentShape = allShapes[shapeChoice - 1];
                            // Remove the chosen shape from allShapes
                            allShapes.erase(allShapes.begin() + shapeChoice - 1);
                        }
                    }
                }

                int row, col;


                // Keep asking until the player makes a valid move
                while (true) {
                    std::cout << "Enter the row and column to place the shape : ";
                    std::cin >> row >> col;

                    if (gameBoard.placeShape(currentShape, player.getNumber(), row, col) && player.canPlaceTile(currentShape)) {
                        // Valid move, break out of the loop
                        break;
                    }
                    else {
                        std::cout << "Invalid move. Try again.\n";
                    }
                } 

                // Display the updated board
                std::cout << "Current Board:\n";
                gameBoard.display();
                std::cout << std::endl;
            }

            // ... (Continue with the rest of the gameplay logic, including bonus squares)
        }
    }

    return 0;
}
