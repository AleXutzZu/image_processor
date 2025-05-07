//
// Created by AleXutzZu on 22/04/2025.
//

#ifndef IMAGE_PROCESSOR_SOBELKERNEL_H
#define IMAGE_PROCESSOR_SOBELKERNEL_H

#include "Kernel.h"

namespace imgproc {

    /**
     * Base class for the sobel kernels. The scaling function maps values from the range [-1020, 1020] into [0, 255].
     */
    class SobelKernel : public Kernel {
    public:
        SobelKernel();

        SobelKernel(const SobelKernel &other) = delete;

        SobelKernel &operator=(const SobelKernel &other) = delete;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_SOBELKERNEL_H
