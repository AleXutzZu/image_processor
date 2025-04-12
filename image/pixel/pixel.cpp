//
// Created by AleXutzZu on 12/04/2025.
//

#include <algorithm>
#include "pixel.h"

namespace imgproc {
    GrayPixel::GrayPixel() : value(0) {}

    GrayPixel::GrayPixel(uint8_t value) : value(value) {}

    GrayPixel operator+(const GrayPixel &lhs, const GrayPixel &rhs) {
        int result = (int) (lhs.value) + (int) (rhs.value);
        result = std::min(result, 255);
        return GrayPixel(result);
    }

    GrayPixel operator-(const GrayPixel &lhs, const GrayPixel &rhs) {
        int result = (int) (lhs.value) - (int) (rhs.value);
        result = std::max(result, 0);
        return GrayPixel(result);
    }
} // imgproc