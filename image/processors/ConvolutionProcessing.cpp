//
// Created by AleXutzZu on 14/04/2025.
//

#include "ConvolutionProcessing.h"
#include "kernels/IdentityKernel.h"

namespace imgproc {
    void ConvolutionProcessing::processImage(const PPMImage &src, PPMImage &dst) {

    }

    void ConvolutionProcessing::processImage(const PGMImage &src, PGMImage &dst) {
        dst = src;

        for (int i = 0; i < dst.getHeight(); ++i) {
            for (int j = 0; j < dst.getWidth(); ++j) {
                applyKernel(i, j, src);
            }
        }
    }

    ConvolutionProcessing::ConvolutionProcessing(Kernel *kernel) : kernel(kernel) {}

    ConvolutionProcessing::ConvolutionProcessing() : kernel() {
        kernel = new IdentityKernel();
    }

    ConvolutionProcessing::~ConvolutionProcessing() {
        delete kernel;
    }

    GrayPixel ConvolutionProcessing::applyKernel(int x, int y, const PGMImage &image) {
        int result = 0;

        for (int i = 0; i < kernel->getHeight(); ++i) {
            for (int j = 0; j < kernel->getWidth(); ++j) {
                int nx = x - j + kernel->getWidth() / 2;
                int ny = y - i + kernel->getHeight() / 2;

                nx = std::max(nx, 0);
                nx = std::min<int>(nx, image.getWidth() - 1);

                ny = std::max(ny, 0);
                ny = std::min<int>(ny, image.getHeight() - 1);

                auto pixel = image.cat(nx, ny);
                result += pixel.getValue() * kernel->at(i, j);
            }
        }
        auto scaled = kernel->getScalingFunction()(result);
        return scaled;
    }
} // imgproc