//
// Created by AleXutzZu on 12/04/2025.
//

#include "Point.h"

namespace imgproc {
    unsigned int Point::getX() const {
        return x;
    }

    unsigned int Point::getY() const {
        return y;
    }

    Point::Point(unsigned int x, unsigned int y) : x(x), y(y) {}

    Point::Point() = default;

    std::ostream &operator<<(std::ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }

    Point operator+(const Point &lhs, const Point &rhs) {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    Point operator-(const Point &lhs, const Point &rhs) {
        return {lhs.x - rhs.x, lhs.y - rhs.y};
    }

    bool Point::operator==(const Point &rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }

    bool Point::operator!=(const Point &rhs) const {
        return !(rhs == *this);
    }
}

