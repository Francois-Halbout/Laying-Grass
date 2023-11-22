#include "Tile.h"
#include <fstream>
#include <iostream>
#include <ctime>  // Include the ctime header for using std::time

Tile::Tile() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(0)));

    // Generate a random tile number between 1 and 96
    int randomTileNumber = std::rand() % 96 + 1;

    std::string fileName = std::to_string(randomTileNumber) + ".txt";
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::vector<std::vector<char>> tileShape;
        char cell;

        while (file >> cell) {
            if (cell == '\n') {
                continue;
            }
            tileShape.push_back({ cell });
        }

        setShape(tileShape);
        file.close();
    }
    else {
        // Handle error: Unable to open the file
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        exit(1);
    }
}

// ... (rest of your Tile class remains the same)


Tile::~Tile() {
}
