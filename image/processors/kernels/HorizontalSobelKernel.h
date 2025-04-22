//
// Created by AleXutzZu on 22/04/2025.
//

#ifndef IMAGE_PROCESSOR_HORIZONTALSOBELKERNEL_H
#define IMAGE_PROCESSOR_HORIZONTALSOBELKERNEL_H

#include "SobelKernel.h"

namespace imgproc {

    class HorizontalSobelKernel : public SobelKernel {
    public:
        HorizontalSobelKernel();

        HorizontalSobelKernel(const HorizontalSobelKernel &other) = delete;

        HorizontalSobelKernel &operator=(const HorizontalSobelKernel &other) = delete;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_HORIZONTALSOBELKERNEL_H
