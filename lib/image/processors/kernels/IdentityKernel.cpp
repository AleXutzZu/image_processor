//
// Created by AleXutzZu on 14/04/2025.
//

#include "IdentityKernel.h"

namespace imgproc {
    IdentityKernel::IdentityKernel() : Kernel(3, 3,
                                              [](int value) -> GrayPixel {
                                                  return GrayPixel(value);
                                              }) {
        data[1][1] = 1;
    }
} // imgproc