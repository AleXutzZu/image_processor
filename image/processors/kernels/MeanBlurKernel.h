//
// Created by AleXutzZu on 16/04/2025.
//

#ifndef IMAGE_PROCESSOR_MEANBLURKERNEL_H
#define IMAGE_PROCESSOR_MEANBLURKERNEL_H

#include "Kernel.h"
#include "../../pixel/pixel.h"

namespace imgproc {

    class MeanBlurKernel final : public Kernel {
    public:
        MeanBlurKernel();

        MeanBlurKernel(const MeanBlurKernel &other) = delete;

        MeanBlurKernel &operator=(const MeanBlurKernel &other) = delete;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_MEANBLURKERNEL_H
