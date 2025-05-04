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

        long long w = (long long) (bottomRight.getX()) - x;
        if (w < 0) throw std::runtime_error("Invalid points");

        long long h = (long long) (bottomRight.getY()) - y;
        if (h < 0) throw std::runtime_error("Invalid points");
        width = w;
        height = h;
    }

    Rectangle operator|(const Rectangle &lhs, const Rectangle &rhs) {
        if (lhs == Rectangle()) return rhs;
        if (rhs == Rectangle()) return lhs;

        unsigned int left = std::min(lhs.x, rhs.x);
        unsigned int top = std::min(lhs.y, rhs.y);
        unsigned int right = std::max(lhs.x + lhs.width, rhs.x + rhs.width);
        unsigned int bottom = std::max(lhs.y + lhs.height, rhs.y + rhs.height);

        return {left, top, right - left, bottom - top};
    }

    Rectangle operator&(const Rectangle &lhs, const Rectangle &rhs) {
        unsigned int inter_left = std::max(lhs.x, rhs.x);
        unsigned int inter_top = std::max(lhs.y, rhs.y);
        unsigned int inter_right = std::min(lhs.x + lhs.width, rhs.x + rhs.width);
        unsigned int inter_bottom = std::min(lhs.y + lhs.height, rhs.y + rhs.height);

        long long inter_width = (long long) (inter_right) - inter_left;
        long long inter_height = (long long) (inter_bottom) - inter_top;
        if (inter_width <= 0 || inter_height <= 0) return {};
        return {inter_left, inter_top, (unsigned int) inter_width, (unsigned int) inter_height};
    }

    std::istream &operator>>(std::istream &is, Rectangle &rectangle) {
        return is >> rectangle.x >> rectangle.y >> rectangle.width >> rectangle.height;
    }

    std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle) {
        return os << rectangle.x << " " << rectangle.y << " " << rectangle.width << " " << rectangle.height;
    }

    unsigned int Rectangle::getX() const {
        return x;
    }

    unsigned int Rectangle::getY() const {
        return y;
    }

    unsigned int Rectangle::getWidth() const {
        return width;
    }

    unsigned int Rectangle::getHeight() const {
        return height;
    }

    bool Rectangle::operator==(const Rectangle &rhs) const {
        return x == rhs.x &&
               y == rhs.y &&
               width == rhs.width &&
               height == rhs.height;
    }

    bool Rectangle::operator!=(const Rectangle &rhs) const {
        return !(rhs == *this);
    }

    Point Rectangle::getCorner() const {
        return {x, y};
    }
} // imgproc