// Shape.cpp

#include "Shape.h"
#include <iostream>

Shape1::Shape1() {
    // Initialize the L-shaped tile
    shape = { {'#', ' ', ' '},
             {'#', ' ', ' '},
             {'#', '#', ' '} };
}

Shape1::~Shape1() {}

void Shape1::rotateClockwise() {
    std::vector<std::vector<char>> newShape(shape[0].size(), std::vector<char>(shape.size()));

    for (size_t i = 0; i < shape.size(); ++i) {
        for (size_t j = 0; j < shape[i].size(); ++j) {
            newShape[j][shape.size() - 1 - i] = shape[i][j];
        }
    }

    shape = newShape;
}

void Shape1::flip() {
    for (size_t i = 0; i < shape.size(); ++i) {
        std::reverse(shape[i].begin(), shape[i].end());
    }
}

void Shape1::display() const {
    for (const auto& row : shape) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}

// Implement the getShape function
const std::vector<std::vector<char>>& Shape1::getShape() const {
    return shape;
}
