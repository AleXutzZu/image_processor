//
// Created by AleXutzZu on 02/05/2025.
//

#ifndef IMAGE_PROCESSOR_DRAWING_H
#define IMAGE_PROCESSOR_DRAWING_H

#include "../image/Image.h"
#include "Point.h"

namespace imgproc::draw {

    /**
     * Draws a circle on the image
     * @tparam T the type of pixel to use for coloring
     * @param image the image to draw the circle in
     * @param center the center of the circle
     * @param radius the radius of the circle
     * @param color the color to use on the boundary of the circle
     */
    template<typename T>
    void drawCircle(Image<T> &image, const Point &center, unsigned int radius, T color) {
        int cx = static_cast<int>(center.getX());
        int cy = static_cast<int>(center.getY());

        int x = radius;
        int y = 0;
        int decision = 1 - radius;

        auto plot = [&](int px, int py) {
            if (px >= 0 && py >= 0 && py < image.getHeight() && px < image.getWidth()) {
                image.at(py, px) = color;
            }
        };

        while (y <= x) {
            plot(cx + x, cy + y);
            plot(cx - x, cy + y);
            plot(cx + x, cy - y);
            plot(cx - x, cy - y);
            plot(cx + y, cy + x);
            plot(cx - y, cy + x);
            plot(cx + y, cy - x);
            plot(cx - y, cy - x);

            y++;
            if (decision <= 0) {
                decision += 2 * y + 1;
            } else {
                x--;
                decision += 2 * (y - x) + 1;
            }
        }
    }


    /**
     * Draws a line on the image
     * @tparam T the type of pixel to use for coloring
     * @param image the image to draw the line in
     * @param p1 the first endpoint of the line
     * @param p2 the second endpoint of the line
     * @param color the color to use for filling in the rectangle
     */
    template<typename T>
    void drawLine(Image<T> &image, const Point &p1, const Point &p2, T color) {
        int x1 = static_cast<int>(p1.getX());
        int y1 = static_cast<int>(p1.getY());
        int x2 = static_cast<int>(p2.getX());
        int y2 = static_cast<int>(p2.getY());

        int delta_x = abs(x2 - x1);
        int delta_y = abs(y2 - y1);
        int step_x = (x1 < x2) ? 1 : -1;
        int step_y = (y1 < y2) ? 1 : -1;
        int error = delta_x - delta_y;

        while (true) {
            if (x1 >= 0 && y1 >= 0 && y1 < image.getHeight() && x1 < image.getWidth()) {
                image.at(x1, y1) = color;
            }

            if (x1 == x2 && y1 == y2) break;
            int double_error = 2 * error;

            if (double_error > -delta_y) {
                error -= delta_y;
                x1 += step_x;
            }

            if (double_error < delta_x) {
                error += delta_x;
                y1 += step_y;
            }
        }
    }

    /**
     * Draws a filled rectangle within the given image
     * @tparam T the type of pixel to use for coloring
     * @param image the image to draw the rectangle in
     * @param tl the top-left corner of the rectangle
     * @param br the bottom-right corner of the rectangle
     * @param color the color to use for filling in the rectangle
     * @throws invalid_argument if the rectangle is not fully contained in the image
     */
    template<typename T>
    void drawRectangle(Image<T> &image, const Point &tl, const Point &br, T color) {
        Rectangle rectangle(tl, br);
        drawRectangle(image, rectangle, color);
    }

    /**
     * Draws a filled rectangle within the given image
     * @tparam T the type of pixel to use for coloring
     * @param image the image to draw the rectangle in
     * @param rectangle the rectangle to draw
     * @param color the color to use for filling in the rectangle
     * @throws invalid_argument if the rectangle is not fully contained in the image
     */
    template<typename T>
    void drawRectangle(Image<T> &image, const Rectangle &rectangle, T color) {
        if (rectangle.getY() + rectangle.getHeight() > image.getHeight() ||
            rectangle.getX() + rectangle.getWidth() > image.getWidth()) {
            throw std::invalid_argument("Rectangle is not within the bounds of the image!");
        }

        for (int i = 0; i < rectangle.getWidth(); ++i) {
            for (int j = 0; j < rectangle.getHeight(); ++j) {
                image.at(rectangle.getX() + i, rectangle.getY() + j) = color;
            }
        }
    }
}
#endif //IMAGE_PROCESSOR_DRAWING_H
