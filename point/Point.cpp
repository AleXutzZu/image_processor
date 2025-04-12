//
// Created by AleXutzZu on 12/04/2025.
//

#include "Point.h"

unsigned int Point::getX() const {
    return x;
}

unsigned int Point::getY() const {
    return y;
}

Point::Point(unsigned int x, unsigned int y) : x(x), y(y) {}
