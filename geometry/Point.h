//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_POINT_H
#define IMAGE_PROCESSOR_POINT_H

#include <iostream>

class Point {
private:
    unsigned int x{};
    unsigned int y{};

public:
    [[nodiscard]] unsigned int getX() const;

    [[nodiscard]] unsigned int getY() const;

    Point(unsigned int x, unsigned int y);

    friend std::ostream& operator<<(std::ostream &os, const Point &p);

    friend Point operator+(const Point &lhs, const Point &rhs);

    friend std::istream &operator>>(std::istream &is, Point &p);
};


#endif //IMAGE_PROCESSOR_POINT_H
