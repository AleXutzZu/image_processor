//
// Created by AleXutzZu on 16/04/2025.
//

#ifndef IMAGE_PROCESSOR_MEANBLURKERNEL_H
#define IMAGE_PROCESSOR_MEANBLURKERNEL_H

#include "Kernel.h"
#include "../../pixel/pixel.h"

namespace imgproc {
    /**
     * Kernel which applies a blur effect. All pixel weights are 1. The scaling function divides the resulted value by 9.
     */
    class MeanBlurKernel final : public Kernel {
    public:
        MeanBlurKernel();

        MeanBlurKernel(const MeanBlurKernel &other) = delete;

        MeanBlurKernel &operator=(const MeanBlurKernel &other) = delete;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_MEANBLURKERNEL_H
