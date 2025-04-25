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

std::ostream &operator<<(std::ostream &os, const Point &p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

std::istream &operator>>(std::istream &is, Point &p) {
    return is >> p.x >> p.y;
}
