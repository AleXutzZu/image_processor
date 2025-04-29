//
// Created by AleXutzZu on 28/04/2025.
//

#include "Rectangle.h"

namespace imgproc {
    Rectangle::Rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) :
            x(x), y(y),
            width(width),
            height(height) {}

    Rectangle::Rectangle() : x(0), y(0), width(0), height(0) {}

    Rectangle::Rectangle(const Point &topLeft, const Point &bottomRight) {
        x = topLeft.getX();
        y = topLeft.getY();

        long long w = bottomRight.getX() - x;
        if (w < 0) throw std::runtime_error("Invalid points");

        long long h = y - bottomRight.getY();
        if (h < 0) throw std::runtime_error("Invalid points");
        width = w;
        height = h;
    }

    Rectangle operator|(const Rectangle &lhs, const Rectangle &rhs) {
        const Rectangle &leftMost = lhs.x < rhs.x ? lhs : rhs;
        const Rectangle &rightMost = lhs.x < rhs.x ? rhs : lhs;

        Point corner1 = Point(leftMost.x, leftMost.y);
        Point corner2 = Point(rightMost.x + rightMost.width, rightMost.y - rightMost.height);
        return {corner1, corner2};
    }

    Rectangle operator&(const Rectangle &lhs, const Rectangle &rhs) {
        unsigned int inter_left = std::max(lhs.x, rhs.x);
        unsigned int inter_top = std::max(lhs.y, rhs.y);
        unsigned int inter_right = std::min(lhs.x + lhs.width, rhs.x + rhs.width);
        unsigned int inter_bottom = std::min(lhs.y + lhs.height, rhs.y + rhs.height);

        long long inter_width = inter_right - inter_left;
        long long inter_height = inter_bottom - inter_top;
        if (inter_width <= 0 || inter_height <= 0) return {};
        return {inter_left, inter_top, (unsigned int) inter_width, (unsigned int) inter_height};
    }
} // imgproc