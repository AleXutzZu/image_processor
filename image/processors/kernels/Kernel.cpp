//
// Created by AleXutzZu on 14/04/2025.
//

#include <stdexcept>
#include "Kernel.h"

namespace imgproc {
    Kernel::Kernel(unsigned int width, unsigned int height, const std::function<GrayPixel(int)> &function) : width(
            width), height(height), scalingFunction(function) {
        if (width < 1 || height < 1) throw std::invalid_argument("Invalid width / height");
        data = new int *[height];
        for (int i = 0; i < height; ++i) {
            data[i] = new int[width];
            for (int j = 0; j < width; ++j) data[i][j] = 0;
        }
    }

    Kernel::~Kernel() {
        if (data != nullptr) {
            for (int i = 0; i < height; ++i) delete[] data[i];
            delete[] data;
        }
    }

    const int &Kernel::at(int i, int j) const {
        if (!_valid(i, j)) throw std::out_of_range("Invalid indices");
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