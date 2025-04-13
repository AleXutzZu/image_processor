//
// Created by AleXutzZu on 12/04/2025.
//

#include "GammaProcessing.h"
#include "../pixel/pixel.h"

namespace imgproc {
    GammaProcessing::GammaProcessing(float gamma) : gamma(gamma) {}

    void GammaProcessing::processImage(const PGMImage &src, PGMImage &dst) {
        dst = src;

        for (int i = 0; i < dst.getHeight(); ++i) {
            for (int j = 0; j < dst.getWidth(); ++j) {
                auto &pixel = dst.at(j, i);
                pixel = power(gamma, pixel);
            }
        }
    }

    void GammaProcessing::processImage(const PPMImage &src, PPMImage &dst) {
        dst = src;
        //TODO
    }

    GammaProcessing::GammaProcessing() : gamma(1) {}
} // imgproc