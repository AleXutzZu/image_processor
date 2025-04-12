//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_ALPHABETAPROCESSING_H
#define IMAGE_PROCESSOR_ALPHABETAPROCESSING_H

#include "../PGMImage.h"
#include "../PPMImage.h"

namespace imgproc {

    class AlphaBetaProcessing : public PGMImageProcessor, public PPMImageProcessor {
    private:
        float alpha, beta;

    public:
        AlphaBetaProcessing();

        void processImage(const PGMImage &src, PGMImage &dst) override;

        void processImage(const PPMImage &src, PPMImage &dst) override;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_ALPHABETAPROCESSING_H
