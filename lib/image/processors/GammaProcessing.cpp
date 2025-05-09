//
// Created by AleXutzZu on 12/04/2025.
//

#include "GammaProcessing.h"
#include "../pixel/pixel.h"

namespace imgproc {
    GammaProcessing::GammaProcessing(float gamma) : gamma(gamma) {}

    void GammaProcessing::processImage(const PGMImage &src, PGMImage &dst) {
        dst = gamma ^ src;
    }

    void GammaProcessing::processImage(const PPMImage &src, PPMImage &dst) {
        dst = gamma ^ src;
    }

    GammaProcessing::GammaProcessing() : gamma(1) {}
} // imgproc