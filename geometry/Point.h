//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_POINT_H
#define IMAGE_PROCESSOR_POINT_H

#include <iostream>

namespace imgproc {

/**
 * Class for representing a 2D point
 */
    class Point {
    private:
        unsigned int x{};
        unsigned int y{};

    public:
        /**
         * Creates a point at the origin of the system, i.e. (0, 0)
         */
        Point();

        /**
         * Creates a point at coordinates (x, y) of the system
         * @param x the x-coordinate
         * @param y the y-coordinate
         */
        Point(unsigned int x, unsigned int y);

        /**
         * Returns the x-coordinate of the point
         * @return the x-coordinate
         */
        [[nodiscard]] unsigned int getX() const;

        /**
         * Returns the y-coordinate of the point
         * @return the y-coordinate
         */
        [[nodiscard]] unsigned int getY() const;

        friend std::ostream &operator<<(std::ostream &os, const Point &p);

        /**
         * Adds two points together by adding their x and y coordinates
         * @param lhs the first point
         * @param rhs the second point
         * @return the point whose coordinates are the sum for each component
         */
        friend Point operator+(const Point &lhs, const Point &rhs);

        /**
         * Subtracts the second point's coordinates from the first one
         * @param lhs the first point
         * @param rhs the second point
         * @return the point whose coordinates are the difference for each component
         */
        friend Point operator-(const Point &lhs, const Point &rhs);

        friend std::istream &operator>>(std::istream &is, Point &p);
    };
}


#endif //IMAGE_PROCESSOR_POINT_H
