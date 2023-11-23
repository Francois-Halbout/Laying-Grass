// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Shape.h"
#include "Tile.h"
#include "Board.h"

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

    int getShapeExchangeCoupons() const;
    void useShapeExchangeCoupon();

    void addTileToTerritory(const Shape1& tile);
    bool canPlaceTile(const Shape1& tile) const;
    void displayTerritory() const;

    int getNumber() const;
    void setNumber(int num);

    void setNextTiles(const std::vector<Shape1>& tiles);
    const std::vector<Shape1>& getNextTiles() const;
    void displayNextTiles() const;
    std::vector<Tile> manipulateTile(std::vector<Tile>& tile);
    void displayEvolution(const Shape1& tile) const;
    void displayNext5Tiles(const std::vector<Tile>& nextTiles) const;
    void displayBoard(const Board& gameBoard) const;

private:
    std::string name;
    char color;
    bool hasStartingTile;
    int tileExchangeCoupons;
    int shapeExchangeCoupons;
    int number;

    std::vector<std::vector<char>> territory;
    std::vector<Shape1> nextTiles;
};

#endif // PLAYER_H
