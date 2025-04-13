//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_GAMMAPROCESSING_H
#define IMAGE_PROCESSOR_GAMMAPROCESSING_H

#include "../PGMImage.h"
#include "../PPMImage.h"

namespace imgproc {

    class GammaProcessing : public PPMImageProcessor, public PGMImageProcessor {
    private:
        float gamma;

    public:
        GammaProcessing();

        explicit GammaProcessing(float gamma);

        void processImage(const PPMImage &src, PPMImage &dst) override;

        void processImage(const PGMImage &src, PGMImage &dst) override;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_GAMMAPROCESSING_H
