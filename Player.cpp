#include "Player.h"
#include <iostream>

Player::Player() : hasStartingTile(false), tileExchangeCoupons(0), shapeExchangeCoupons(0), number(0) {
    // Initialize territory with an empty 2D vector
    territory.resize(3, std::vector<char>());
}

// Implement the getNumber method
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

void Player::setColor(const std::string& playerColor) {
    color = playerColor;
}

std::string Player::getColor() const {
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
    // Add the tile to the player's territory
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
    // Check if the tile can be placed according to the rules
    // (touching the starting tile and not overlapping)
    // Implement this based on your game rules.
    // For simplicity, this example assumes that the tile must touch the existing territory.
    // You may need to modify this according to your specific game rules.
    return true;
}

void Player::displayTerritory() const {
    // Display the player's territory
    std::cout << "Player " << name << "'s Territory:\n";
    for (const auto& row : territory) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}

// Implement the setNumber method
void Player::setNumber(int num) {
    number = num;
}
