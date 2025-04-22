//
// Created by AleXutzZu on 22/04/2025.
//

#ifndef IMAGE_PROCESSOR_VERTICALSOBELKERNEL_H
#define IMAGE_PROCESSOR_VERTICALSOBELKERNEL_H

#include "SobelKernel.h"

namespace imgproc {

    class VerticalSobelKernel : public SobelKernel {
    public:
        VerticalSobelKernel();

        VerticalSobelKernel(const VerticalSobelKernel &other) = delete;

        VerticalSobelKernel &operator=(const VerticalSobelKernel &other) = delete;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_VERTICALSOBELKERNEL_H
