// Player.cpp
#include "Player.h"
#include <iostream>

Player::Player() : hasStartingTile(false), tileExchangeCoupons(0), shapeExchangeCoupons(0), number(0) {
    territory.resize(3, std::vector<char>());
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

void Player::setNextTiles(const std::vector<Shape1>& tiles) {
    nextTiles = tiles;
}

const std::vector<Shape1>& Player::getNextTiles() const {
    return nextTiles;
}

void Player::displayNextTiles() const {
    std::cout << "Next tiles:\n";
    for (const auto& tile : nextTiles) {
        tile.display();
    }
}

void Player::manipulateTile(Shape1& tile) {
    char choice;
    std::cout << "Manipulate the tile (R: Rotate, F: Flip, X: Do nothing): ";
    std::cin >> choice;

    if (choice == 'R') {
        tile.rotateClockwise();
    }
    else if (choice == 'F') {
        tile.flip();
    }
}