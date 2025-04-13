//
// Created by AleXutzZu on 12/04/2025.
//

#include "AlphaBetaProcessing.h"

namespace imgproc {
    AlphaBetaProcessing::AlphaBetaProcessing() : alpha(1), beta(0) {}

    void AlphaBetaProcessing::processImage(const PGMImage &src, PGMImage &dst) {
        dst = src;
        dst = beta + (alpha * dst);
    }

    void AlphaBetaProcessing::processImage(const PPMImage &src, PPMImage &dst) {
        //TODO
    }

    AlphaBetaProcessing::AlphaBetaProcessing(float alpha, float beta) : alpha(alpha), beta(beta) {}
} // imgproc