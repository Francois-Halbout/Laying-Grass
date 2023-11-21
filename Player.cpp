#include "Player.h"
#include <iostream>

Player::Player() : hasStartingTile(false), tileExchangeCoupons(0), shapeExchangeCoupons(0), number(0) {
    // Initialiser le territoire avec un vecteur 2D vide
    territory.resize(3, std::vector<char>());
}

// Impl�menter la m�thode getNumber
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
    // Ajouter la tuile au territoire du joueur
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
    // V�rifier si la tuile peut �tre plac�e selon les r�gles
    // (toucher la tuile de d�part et ne pas se chevaucher)
    // Impl�mentez cela en fonction de vos r�gles de jeu.
    // Pour simplifier, cet exemple suppose que la tuile doit toucher le territoire existant.
    // Vous devrez peut-�tre modifier cela en fonction de vos r�gles sp�cifiques du jeu.
    return true;
}

void Player::displayTerritory() const {
    // Afficher le territoire du joueur
    std::cout << "Territoire du joueur " << name << ":\n";
    for (const auto& row : territory) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}

// Impl�menter la m�thode setNumber
void Player::setNumber(int num) {
    number = num;
}
