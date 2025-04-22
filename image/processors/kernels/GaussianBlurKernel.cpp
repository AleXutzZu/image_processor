//
// Created by AleXutzZu on 16/04/2025.
//

#include "GaussianBlurKernel.h"

namespace imgproc {
    GaussianBlurKernel::GaussianBlurKernel() : Kernel(3, 3,
                                                      [](int result) -> GrayPixel {
                                                          return GrayPixel(result / 16);
                                                      }) {
        data[0][0] = data[0][2] = data[2][0] = data[2][2] = 1;
        data[0][1] = data[1][0] = data[1][2] = data[2][1] = 2;
        data[1][1] = 4;
    }
} // imgproc