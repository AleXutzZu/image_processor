//
// Created by AleXutzZu on 28/04/2025.
//

#ifndef IMAGE_PROCESSOR_RECTANGLE_H
#define IMAGE_PROCESSOR_RECTANGLE_H

#include "Point.h"

namespace imgproc {

    class Rectangle {
    private:
        unsigned int x, y;
        unsigned int width;
        unsigned int height;

    public:
        Rectangle();

        Rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

        Rectangle(const Point &topLeft, const Point &bottomRight);

        friend Rectangle operator|(const Rectangle &lhs, const Rectangle &rhs);

        friend Rectangle operator&(const Rectangle &lhs, const Rectangle &rhs);

        friend std::istream &operator>>(std::istream &is, Rectangle &rectangle);

        friend std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle);

        [[nodiscard]] unsigned int getX() const;

        [[nodiscard]] unsigned int getY() const;

        [[nodiscard]] unsigned int getWidth() const;

        bool operator==(const Rectangle &rhs) const;

        bool operator!=(const Rectangle &rhs) const;

        [[nodiscard]] unsigned int getHeight() const;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_RECTANGLE_H
