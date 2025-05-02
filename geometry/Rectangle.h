//
// Created by AleXutzZu on 28/04/2025.
//

#ifndef IMAGE_PROCESSOR_RECTANGLE_H
#define IMAGE_PROCESSOR_RECTANGLE_H

#include "Point.h"

namespace imgproc {
    /**
     * Class to represent a basic Rectangle shape
     */
    class Rectangle {
    private:
        unsigned int x, y;
        unsigned int width;
        unsigned int height;

    public:
        /**
         * Constructs a rectangle with all values set to 0
         */
        Rectangle();
        /**
         * Constructs a rectangle given the top-left corner, a width and a height
         * @param x the x-coordinate for the top-left corner
         * @param y the y-coordinate for the top-left corner
         * @param width the width of the rectangle
         * @param height the height of the rectangle
         */
        Rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        /**
         * Constructs a rectangle given the top-left and bottom-right corners
         * @param topLeft the top-left corner of the rectangle
         * @param bottomRight the bottom-right corner of the rectangle
         * @throws runtime_error if the specified coordinates would produce a rectangle with negative width/height
         */
        Rectangle(const Point &topLeft, const Point &bottomRight);

        /**
         * Performs the union of two rectangles
         * @param lhs the first rectangle
         * @param rhs the other rectangle
         * @return the smallest rectangle which contains both @a lhs and @a rhs
         */
        friend Rectangle operator|(const Rectangle &lhs, const Rectangle &rhs);

        /***
         * Performs he intersection of two rectangles
         * @param lhs the first rectangle
         * @param rhs the second rectangle
         * @return the rectangle at the intersection of @a lhs with @a rhs
         */
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
