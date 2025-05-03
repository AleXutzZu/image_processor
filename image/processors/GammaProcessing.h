//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_GAMMAPROCESSING_H
#define IMAGE_PROCESSOR_GAMMAPROCESSING_H

#include "../PGMImage.h"
#include "../PPMImage.h"

namespace imgproc {
    /**
     * Processor responsible for applying a gamma correction on the PPM and PGM image formats
     */
    class GammaProcessing : public PPMImageProcessor, public PGMImageProcessor {
    private:
        float gamma;

    public:
        /**
         * Constructs a default no-op processor with a gamma value of 1
         */
        GammaProcessing();
        /**
         * Constructs a gamma processor with the specified value
         * @param gamma the gamma correction to apply on images
         */
        explicit GammaProcessing(float gamma);

        /**
         * Applies gamma correction to PPM images
         * @param src the source image
         * @param dst the modified image
         */
        void processImage(const PPMImage &src, PPMImage &dst) override;

        /**
         * Applies gamma correction to PGM images
         * @param src the source image
         * @param dst the modified image
         */
        void processImage(const PGMImage &src, PGMImage &dst) override;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_GAMMAPROCESSING_H
