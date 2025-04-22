//
// Created by AleXutzZu on 16/04/2025.
//

#ifndef IMAGE_PROCESSOR_GAUSSIANBLURKERNEL_H
#define IMAGE_PROCESSOR_GAUSSIANBLURKERNEL_H

#include "Kernel.h"
#include "../../pixel/pixel.h"

namespace imgproc {

    class GaussianBlurKernel : public Kernel {
    public:
        GaussianBlurKernel();

        GaussianBlurKernel(const GaussianBlurKernel &other) = delete;

        GaussianBlurKernel &operator=(const GaussianBlurKernel &other) = delete;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_GAUSSIANBLURKERNEL_H
