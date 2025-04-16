//
// Created by AleXutzZu on 16/04/2025.
//

#include "MeanBlurKernel.h"

namespace imgproc {
    MeanBlurKernel::MeanBlurKernel() : Kernel(3, 3) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) data[i][j] = 1;
        }
    }

    GrayPixel MeanBlurKernel::scale(int other) {
        return GrayPixel(other / 9);
    }
} // imgproc