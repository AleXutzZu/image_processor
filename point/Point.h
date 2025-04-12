//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_POINT_H
#define IMAGE_PROCESSOR_POINT_H


class Point {
private:
    unsigned int x{};
    unsigned int y{};

public:
    unsigned int getX() const;

    unsigned int getY() const;

    Point(unsigned int x, unsigned int y);
};


#endif //IMAGE_PROCESSOR_POINT_H
