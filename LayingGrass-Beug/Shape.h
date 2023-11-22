// Shape.h
#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

class Shape1 {
public:
    Shape1(); // Default constructor
    Shape1(const std::vector<std::vector<char>>& initialShape);
    ~Shape1();

    void setShape(const std::vector<std::vector<char>>& newShape);  // New function to set the shape

    void rotateClockwise();
    void flip();

    void display() const;

    const std::vector<std::vector<char>>& getShape() const;
    int getHeight() const;
    int getWidth() const;
    char getCell(int row, int col) const;

private:
    std::vector<std::vector<char>> shape;
};

#endif // SHAPE_H
