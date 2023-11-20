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

    void setColor(const std::string& color);
    std::string getColor() const;

    void giveStartingTile();
    void giveTileExchangeCoupon();

    // Add these methods for shape exchange coupons
    int getShapeExchangeCoupons() const;
    void useShapeExchangeCoupon();

    void addTileToTerritory(const Shape1& tile);
    bool canPlaceTile(const Shape1& tile) const;
    void displayTerritory() const;

    int getNumber() const;
    // Add this method to set the player's number
    void setNumber(int num);

private:
    std::string name;
    std::string color;
    bool hasStartingTile;
    int tileExchangeCoupons;
    int shapeExchangeCoupons;
    int number;

    std::vector<std::vector<char>> territory;
};

#endif // PLAYER_H
