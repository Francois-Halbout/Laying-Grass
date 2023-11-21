#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Shape.h"

class Player {
public:
    Player();
    ~Player();

    void setName(const std::string& name);
    std::string getName() const;

    void setColor(char color);

    char getColor() const;

    void giveStartingTile();
    void giveTileExchangeCoupon();

    // Ajouter ces méthodes pour les coupons d'échange de formes
    int getShapeExchangeCoupons() const;
    void useShapeExchangeCoupon();

    void addTileToTerritory(const Shape1& tile);
    bool canPlaceTile(const Shape1& tile) const;
    void displayTerritory() const;

    int getNumber() const;
    // Ajouter cette méthode pour définir le numéro du joueur
    void setNumber(int num);

private:
    std::string name;
    char color;  // Déclaré une seule fois ici comme un char
    bool hasStartingTile;
    int tileExchangeCoupons;
    int shapeExchangeCoupons;
    int number;

    std::vector<std::vector<char>> territory;
};

#endif // PLAYER_H
