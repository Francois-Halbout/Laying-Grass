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

    // Add this member function to get the shape
    const std::vector<std::vector<char>>& getShape() const;

private:
    std::vector<std::vector<char>> shape;
};

#endif // SHAPE_H
