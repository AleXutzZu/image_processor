//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_ALPHABETAPROCESSING_H
#define IMAGE_PROCESSOR_ALPHABETAPROCESSING_H

#include "../PGMImage.h"

namespace imgproc {

    class AlphaBetaProcessing : public PGMImageProcessor {
    private:
        float alpha, beta;

    public:
        AlphaBetaProcessing();

        void processImage(const PGMImage &src, PGMImage &dst) override;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_ALPHABETAPROCESSING_H
