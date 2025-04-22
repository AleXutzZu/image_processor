//
// Created by AleXutzZu on 22/04/2025.
//

#include "SobelKernel.h"

namespace imgproc {
    SobelKernel::SobelKernel() : Kernel(3, 3,
                                        [](int value) -> GrayPixel {
                                            // [ -4 * 255, 4 * 255 ] -> [ 0, 255 ]
                                            int mapped = (value - (-4 * 255)) * 255 / (4 * 255.0 - (-4) * 255);
                                            return GrayPixel(mapped);
                                        }) {}
} // imgproc