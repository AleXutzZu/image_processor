//
// Created by AleXutzZu on 12/04/2025.
//

#include <algorithm>
#include "pixel.h"
#include <cmath>

namespace imgproc {
    GrayPixel::GrayPixel() : value(0) {}

    GrayPixel::GrayPixel(uint8_t value) : value(value) {}

    GrayPixel operator+(const GrayPixel &lhs, const GrayPixel &rhs) {
        int result = (int) (lhs.value) + (int) (rhs.value);
        return GrayPixel(GrayPixel::clip(result));
    }

    GrayPixel operator-(const GrayPixel &lhs, const GrayPixel &rhs) {
        int result = (int) (lhs.value) - (int) (rhs.value);
        return GrayPixel(GrayPixel::clip(result));
    }

    GrayPixel operator+(const float scalar, const GrayPixel &vector) {
        float result = vector.value + scalar;
        return GrayPixel(GrayPixel::clip(result));
    }

    GrayPixel operator*(const float scalar, const GrayPixel &vector) {
        float result = vector.value * scalar;
        return GrayPixel(GrayPixel::clip(result));
    }

    uint8_t GrayPixel::clip(int value) {
        if (value < 0) return 0;
        if (value > 255) return 255;
        return value;
    }

    GrayPixel power(float scalar, const GrayPixel &vector) {
        int result = std::pow(vector.value, scalar);
        return GrayPixel(GrayPixel::clip(result));
    }

    std::ostream &operator<<(std::ostream &os, const GrayPixel &pixel) {
        return os << (int) pixel.value;
    }

    uint8_t GrayPixel::getValue() const {
        return value;
    }


    RGBPixel::RGBPixel() : red(), green(), blue() {}
} // imgproc