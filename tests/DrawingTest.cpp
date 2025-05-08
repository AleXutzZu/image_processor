//
// Created by AleXutzZu on 08/05/2025.
//

#include "gtest/gtest.h"
#include "../geometry/drawing.h"
#include "../image/PGMImage.h"
#include "../image/PPMImage.h"
#include <algorithm>

using imgproc::PGMImage;
using imgproc::Point;
using imgproc::PPMImage;
using imgproc::draw::drawLine;
using imgproc::draw::drawCircle;
using imgproc::draw::drawRectangle;

TEST(DrawingTest, DrawHorizontalLine) {
    PGMImage img(5, 5);
    drawLine(img, Point(1, 2), Point(3, 2), imgproc::GrayPixel(255));

    for (int x = 0; x < 5; ++x) {
        if (x >= 1 && x <= 3) {
            EXPECT_EQ(img.cat(x, 2).getValue(), 255);
        } else {
            EXPECT_EQ(img.cat(x, 2).getValue(), 0);
        }
    }
}

TEST(DrawingTest, DrawVerticalLine) {
    PPMImage img(10, 10);
    const imgproc::RGBPixel &white = imgproc::RGBPixel(255, 255, 255);
    const imgproc::RGBPixel &black = imgproc::RGBPixel(0, 0, 0);

    drawLine(img, Point(1, 2), Point(1, 4), white);

    for (int y = 0; y < 10; ++y) {
        if (y >= 2 && y <= 4) {
            EXPECT_EQ(img.cat(1, y), white);
        } else {
            EXPECT_EQ(img.cat(1, y), black);
        }
    }
}


TEST(DrawingTest, DrawLineOutOfImage) {
    PGMImage img(5, 5);
    drawLine(img, Point(10, 10), Point(20, 20), imgproc::GrayPixel(100));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            EXPECT_EQ(img.cat(i, j).getValue(), 0);
        }
    }
}

TEST(DrawingTest, DrawLineDiagonal) {
    PGMImage expected(5, 5);
    for (size_t i = 0; i < expected.getWidth(); ++i) {
        expected.at(i, i) = imgproc::GrayPixel(255);
    }

    PGMImage actual(5, 5);

    drawLine(actual, Point(0, 0), Point(4, 4), imgproc::GrayPixel(255));

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            EXPECT_EQ(actual.cat(i, j), expected.cat(i, j));
        }
    }
}

TEST(DrawingTest, CircleRadius1Center2x2) {
    int w = 5, h = 5;
    PGMImage img(w, h);
    drawCircle(img, Point(2, 2), 1u, imgproc::GrayPixel(255));

    std::vector<Point> expected = {
            {3, 2},
            {1, 2},
            {2, 3},
            {2, 1},
            {3, 3},
            {1, 3},
            {1, 1},
            {3, 1}
    };

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            bool shouldBeOn = std::find(expected.begin(), expected.end(),
                                        Point(x, y)) != expected.end();
            if (shouldBeOn) {
                EXPECT_EQ(img.cat(x, y).getValue(), 255);
            } else {
                EXPECT_EQ(img.cat(x, y).getValue(), 0);
            }
        }
    }
}

TEST(DrawingTest, CircleRadius2Center2x2) {
    int w = 7, h = 7;
    PGMImage img(w, h);
    drawCircle(img, Point(3, 3), 2u, imgproc::GrayPixel(255));

    std::vector<Point> expected = {
            {5, 3},
            {1, 3},
            {3, 5},
            {3, 1},
            {4, 5},
            {2, 5},
            {1, 4},
            {1, 2},
            {2, 1},
            {4, 1},
            {5, 2},
            {5, 4}
    };

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            bool shouldBeOn = std::find(expected.begin(), expected.end(),
                                        Point(x, y)) != expected.end();
            if (shouldBeOn) {
                EXPECT_EQ(img.cat(x, y).getValue(), 255);
            } else {
                EXPECT_EQ(img.cat(x, y).getValue(), 0);
            }
        }
    }
}

TEST(DrawingTest, CirclePartiallyOutOfBounds) {
    int w = 5, h = 5;
    PGMImage img(w, h);
    drawCircle(img, Point(0, 0), 2u, imgproc::GrayPixel(255));

    std::vector<Point> expected = {
            {0, 2},
            {1, 2},
            {2, 0},
            {2, 1}
    };

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            bool shouldBeOn = std::find(expected.begin(), expected.end(),
                                        Point(x, y)) != expected.end();
            if (shouldBeOn) {
                EXPECT_EQ(img.cat(x, y).getValue(), 255);
            } else {
                EXPECT_EQ(img.cat(x, y).getValue(), 0);
            }
        }
    }
}

TEST(DrawingTest, FillsCorrectPixels) {
    PGMImage image(5, 5);

    imgproc::Rectangle rect(1, 1, 3, 2); // x=1, y=1, width=3, height=2
    imgproc::GrayPixel color(128);

    drawRectangle(image, rect, color);

    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 2; ++j) {
            EXPECT_EQ(image.cat(i, j).getValue(), 128);
        }
    }
}

TEST(DrawingTest, DoesNotTouchOutsidePixels) {
    PGMImage image(5, 5);

    imgproc::Rectangle rect(0, 0, 2, 2); // top-left corner
    imgproc::GrayPixel color(200);
    drawRectangle(image, rect, color);

    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            if (x < 2 && y < 2) {
                EXPECT_EQ(image.cat(x, y).getValue(), 200);
            } else {
                EXPECT_EQ(image.cat(x, y).getValue(), 0);
            }
        }
    }
}

TEST(DrawingTest, ThrowsOnOutOfBounds) {
    PGMImage image(5, 5);

    imgproc::Rectangle rect(3, 3, 3, 3);
    imgproc::GrayPixel color(100);
    EXPECT_THROW(drawRectangle(image, rect, color), std::invalid_argument);
}

TEST(DrawingTest, CanFillFullImage) {
    PGMImage image(5, 5);

    imgproc::Rectangle rect(0, 0, 5, 5);
    imgproc::GrayPixel color(255);
    drawRectangle(image, rect, color);

    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            EXPECT_EQ(image.cat(x, y).getValue(), 255);
        }
    }
}