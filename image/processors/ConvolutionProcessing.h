//
// Created by AleXutzZu on 14/04/2025.
//

#ifndef IMAGE_PROCESSOR_CONVOLUTIONPROCESSING_H
#define IMAGE_PROCESSOR_CONVOLUTIONPROCESSING_H

#include "../PGMImage.h"
#include "../PPMImage.h"
#include "kernels/Kernel.h"
#include <functional>

namespace imgproc {

    class ConvolutionProcessing : public PGMImageProcessor, public PPMImageProcessor {
    private:
        std::function<GrayPixel(int)> scalingFunction;
        Kernel *kernel;

        GrayPixel applyKernel(int x, int y, const PGMImage &image);

        RGBPixel applyKernel(int x, int y, PPMImage &image);

    public:
        ConvolutionProcessing();

        ConvolutionProcessing(const std::function<GrayPixel(int)> &scalingFunction, Kernel *kernel);

        void processImage(const PPMImage &src, PPMImage &dst) override;

        void processImage(const PGMImage &src, PGMImage &dst) override;

        ~ConvolutionProcessing() override;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_CONVOLUTIONPROCESSING_H
