//
// Created by AleXutzZu on 14/04/2025.
//

#ifndef IMAGE_PROCESSOR_IDENTITYKERNEL_H
#define IMAGE_PROCESSOR_IDENTITYKERNEL_H

#include "Kernel.h"
#include "../../pixel/pixel.h"

namespace imgproc {
    /**
     * No-op kernel which does not alter the image. The scaling function returns the value itself after applying this kernel,
     * which in this case would be the original pixel value
     */
    class IdentityKernel : public Kernel {
    public:
        IdentityKernel();

        IdentityKernel(const IdentityKernel &other) = delete;

        IdentityKernel &operator=(const IdentityKernel &other) = delete;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_IDENTITYKERNEL_H
