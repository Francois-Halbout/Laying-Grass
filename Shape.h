// Shape.h

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

class Shape1 {
public:
    Shape1();
    ~Shape1();

    void rotateClockwise();
    void flip();

    void display() const;

    // Ajoutez ces fonctions pour obtenir la forme, la hauteur et la largeur
    const std::vector<std::vector<char>>& getShape() const;
    int getHeight() const;
    int getWidth() const;
    char getCell(int row, int col) const;

private:
    std::vector<std::vector<char>> shape;
};

#endif // SHAPE_H
