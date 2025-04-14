//
// Created by AleXutzZu on 14/04/2025.
//

#include <stdexcept>
#include "Kernel.h"

namespace imgproc {
    Kernel::Kernel(unsigned int width, unsigned int height) : width(width), height(height) {}

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
} // imgproc