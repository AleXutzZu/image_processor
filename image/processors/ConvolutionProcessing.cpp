//
// Created by AleXutzZu on 14/04/2025.
//

#include "ConvolutionProcessing.h"

namespace imgproc {
    void ConvolutionProcessing::processImage(const PPMImage &src, PPMImage &dst) {

    }

    void ConvolutionProcessing::processImage(const PGMImage &src, PGMImage &dst) {

    }

    ConvolutionProcessing::ConvolutionProcessing(const std::function<GrayPixel(GrayPixel)> &scalingFunction,
                                                 const Kernel &kernel) :
            scalingFunction(scalingFunction),
            kernel(kernel) {}

    ConvolutionProcessing::ConvolutionProcessing() {
        scalingFunction = [](const GrayPixel &ref) -> GrayPixel { return ref; };
        //todo identity kernel
    }
} // imgproc