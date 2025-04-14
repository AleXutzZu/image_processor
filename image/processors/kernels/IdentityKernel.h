//
// Created by AleXutzZu on 14/04/2025.
//

#ifndef IMAGE_PROCESSOR_IDENTITYKERNEL_H
#define IMAGE_PROCESSOR_IDENTITYKERNEL_H

#include "Kernel.h"

namespace imgproc {

    class IdentityKernel : public Kernel {
    public:
        IdentityKernel();

        IdentityKernel(const IdentityKernel &other) = delete;

        IdentityKernel &operator=(const IdentityKernel &other) = delete;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_IDENTITYKERNEL_H
