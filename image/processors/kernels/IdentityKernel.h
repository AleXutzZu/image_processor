//
// Created by AleXutzZu on 14/04/2025.
//

#ifndef IMAGE_PROCESSOR_IDENTITYKERNEL_H
#define IMAGE_PROCESSOR_IDENTITYKERNEL_H

#include "Kernel.h"
#include "../../pixel/pixel.h"

namespace imgproc {

    class IdentityKernel : public Kernel {
    public:
        IdentityKernel();

        IdentityKernel(const IdentityKernel &other) = delete;

        IdentityKernel &operator=(const IdentityKernel &other) = delete;

        static GrayPixel scale(int value);
    };

} // imgproc

#endif //IMAGE_PROCESSOR_IDENTITYKERNEL_H
