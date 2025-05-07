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
        long double result = std::pow(vector.value, scalar);

        if (result > 255) return GrayPixel(255);

        auto casted = (uint8_t) result;

        return GrayPixel(casted);
    }

    std::ostream &operator<<(std::ostream &os, const GrayPixel &pixel) {
        return os << (int) pixel.value;
    }

    uint8_t GrayPixel::getValue() const {
        return value;
    }

    bool operator==(const GrayPixel &lhs, const GrayPixel &rhs) {
        return lhs.value == rhs.value;
    }

    bool operator!=(const GrayPixel &lhs, const GrayPixel &rhs) {
        return !(rhs == lhs);
    }


    RGBPixel::RGBPixel() = default;

    bool operator==(const RGBPixel &lhs, const RGBPixel &rhs) {
        for (int i = 0; i < 3; ++i) {
            if (lhs.pixels[i] != rhs.pixels[i]) return false;
        }
        return true;
    }

    bool operator!=(const RGBPixel &lhs, const RGBPixel &rhs) {
        return !(rhs == lhs);
    }

    RGBPixel::RGBPixel(uint8_t red, uint8_t green, uint8_t blue) {
        pixels[0] = GrayPixel(red);
        pixels[1] = GrayPixel(green);
        pixels[2] = GrayPixel(blue);
    }

    RGBPixel operator+(const RGBPixel &lhs, const RGBPixel &rhs) {
        GrayPixel values[3];
        for (int i = 0; i < 3; ++i) {
            values[i] = lhs.pixels[i] + rhs.pixels[i];
        }
        return {values[0].getValue(), values[1].getValue(), values[2].getValue()};
    }

    RGBPixel operator-(const RGBPixel &lhs, const RGBPixel &rhs) {
        GrayPixel values[3];
        for (int i = 0; i < 3; ++i) {
            values[i] = lhs.pixels[i] - rhs.pixels[i];
        }
        return {values[0].getValue(), values[1].getValue(), values[2].getValue()};
    }

    RGBPixel operator+(float scalar, const RGBPixel &vector) {
        GrayPixel values[3];
        for (int i = 0; i < 3; ++i) {
            values[i] = scalar + vector.pixels[i];
        }
        return {values[0].getValue(), values[1].getValue(), values[2].getValue()};
    }

    RGBPixel operator*(float scalar, const RGBPixel &vector) {
        GrayPixel values[3];
        for (int i = 0; i < 3; ++i) {
            values[i] = scalar * vector.pixels[i];
        }
        return {values[0].getValue(), values[1].getValue(), values[2].getValue()};
    }

    RGBPixel power(float scalar, const RGBPixel &vector) {
        GrayPixel values[3];
        for (int i = 0; i < 3; ++i) {
            values[i] = power(scalar, vector.pixels[i]);
        }
        return {values[0].getValue(), values[1].getValue(), values[2].getValue()};
    }

    std::ostream &operator<<(std::ostream &os, const RGBPixel &pixel) {
        return os << pixel.pixels[0] << " " << pixel.pixels[1] << " " << pixel.pixels[2];
    }

    GrayPixel RGBPixel::getRed() const {
        return pixels[0];
    }

    GrayPixel RGBPixel::getGreen() const {
        return pixels[1];
    }

    GrayPixel RGBPixel::getBlue() const {
        return pixels[2];
    }
} // imgproc