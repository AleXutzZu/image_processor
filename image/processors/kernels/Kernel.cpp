//
// Created by AleXutzZu on 14/04/2025.
//

#include <stdexcept>
#include "Kernel.h"

namespace imgproc {
    Kernel::Kernel(unsigned int width, unsigned int height, const std::function<GrayPixel(int)> &function) : width(
            width), height(height), scalingFunction(function) {
        data = new int *[height];
        for (int i = 0; i < 3; ++i) {
            data[i] = new int[3];
            for (int j = 0; j < 3; ++j) data[i][j] = 0;
        }
    }

    Kernel::~Kernel() {
        if (data != nullptr) {
            for (int i = 0; i < height; ++i) delete[] data[i];
        }
    }

    const int &Kernel::at(int i, int j) const {
        if (!_valid(i, j)) throw std::runtime_error("Invalid indices");
        if (data == nullptr) throw std::runtime_error("No data in kernel");
        return data[i][j];
    }

    bool Kernel::_valid(int i, int j) const {
        return 0 <= i && i < height && 0 <= j && j < width;
    }

    unsigned int Kernel::getWidth() const {
        return width;
    }

    unsigned int Kernel::getHeight() const {
        return height;
    }

    const std::function<GrayPixel(int)> &Kernel::getScalingFunction() const {
        return scalingFunction;
    }
} // imgproc