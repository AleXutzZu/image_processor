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
} // imgproc