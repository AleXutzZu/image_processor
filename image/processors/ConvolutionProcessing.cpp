//
// Created by AleXutzZu on 14/04/2025.
//

#include "ConvolutionProcessing.h"
#include "kernels/IdentityKernel.h"

namespace imgproc {
    void ConvolutionProcessing::processImage(const PPMImage &src, PPMImage &dst) {
        dst = (*this->kernel) * src;
    }

    void ConvolutionProcessing::processImage(const PGMImage &src, PGMImage &dst) {
        dst = (*this->kernel) * src;
    }

    ConvolutionProcessing::ConvolutionProcessing(Kernel *kernel) : kernel(kernel) {}

    ConvolutionProcessing::ConvolutionProcessing() : kernel() {
        kernel = new IdentityKernel();
    }

    ConvolutionProcessing::~ConvolutionProcessing() {
        delete kernel;
    }
} // imgproc