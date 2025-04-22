//
// Created by AleXutzZu on 22/04/2025.
//

#ifndef IMAGE_PROCESSOR_SOBELKERNEL_H
#define IMAGE_PROCESSOR_SOBELKERNEL_H

#include "Kernel.h"

namespace imgproc {

    class SobelKernel : public Kernel {
    public:
        SobelKernel();

        SobelKernel(const SobelKernel &other) = delete;

        SobelKernel &operator=(const SobelKernel &other) = delete;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_SOBELKERNEL_H
