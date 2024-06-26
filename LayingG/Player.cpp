// Player.cpp
#include "Player.h"
#include <iostream>


Player::Player() : hasStartingTile(false), tileExchangeCoupons(0), shapeExchangeCoupons(0), number(0) {
    territory.resize(3, std::vector<char>());
    indexTile = 0;
    haveSkip = true;
}

int Player::getNumber() const {
    return number;
}

Player::~Player() {}

void Player::setName(const std::string& playerName) {
    name = playerName;
}

std::string Player::getName() const {
    return name;
}

void Player::setColor(char playerColor) {
    color = playerColor;
}

char Player::getColor() const {
    return color;
}

void Player::giveStartingTile() {
    hasStartingTile = true;
}

void Player::giveTileExchangeCoupon() {
    tileExchangeCoupons++;
}

int Player::getShapeExchangeCoupons() const {
    return shapeExchangeCoupons;
}

void Player::useShapeExchangeCoupon() {
    shapeExchangeCoupons--;
}

void Player::addTileToTerritory(const Shape1& tile) {
    const auto& tileShape = tile.getShape();
    for (size_t i = 0; i < tileShape.size(); ++i) {
        for (size_t j = 0; j < tileShape[i].size(); ++j) {
            if (tileShape[i][j] != ' ') {
                territory[i].push_back(tileShape[i][j]);
            }
        }
    }
}

bool Player::canPlaceTile(const Shape1& tile) const {
    return true;  // Implement according to your game rules
}

void Player::displayTerritory() const {
    std::cout << "Territoire du joueur " << name << ":\n";
    for (const auto& row : territory) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}

void Player::setNumber(int num) {
    number = num;
}

void Player::setNextTiles(int& indexTile) {
    indexTile = indexTile + 1;
}

const std::vector<Shape1>& Player::getNextTiles() const {
    return nextTiles;
}


// Inside the Player class implementation
Shape1 Player::manipulateTile(Shape1& tile) {
    Shape1& currentTile = tile;
    char choice;

    do {
        std::cout << "Manipulate the tile (R: Rotate, F: Flip, X: Do nothing): ";
        std::cin >> choice;

        if (choice == 'R') {
            currentTile.rotateClockwise();
            displayEvolution(currentTile);
        }
        else if (choice == 'F') {
            currentTile.flip();
            displayEvolution(currentTile);
        }
    } while (choice == 'R' || choice == 'F');
    return tile;
}

void Player::displayEvolution(const Shape1& tile) const {
    std::cout << "Current Tile:\n";
    tile.display();

    for (const auto& nextTile : nextTiles) {
        nextTile.display();
    }
}

void Player::displayNext5Tiles(int indexTile, std::vector<Shape1> allTiles) const {

    for (int i = 1; i < std::min(6, static_cast<int>(allTiles.size())); ++i) {
        std::cout << "Next tiles (" << i << "):\n";
        allTiles.at(i + indexTile).display();
    }
}