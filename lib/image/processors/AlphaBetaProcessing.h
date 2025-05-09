//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_ALPHABETAPROCESSING_H
#define IMAGE_PROCESSOR_ALPHABETAPROCESSING_H

#include "../PGMImage.h"
#include "../PPMImage.h"

namespace imgproc {
    /**
     * Processor responsible for applying alpha-beta corrections on the PPM and PGM image formats
     */
    class AlphaBetaProcessing : public PGMImageProcessor, public PPMImageProcessor {
    private:
        float alpha, beta;

    public:
        /**
         * Constructs an alpha-beta processor with the specified values
         * @param alpha the alpha value
         * @param beta the beta value
         */
        AlphaBetaProcessing(float alpha, float beta);

        /**
         * Constructs a default no-op processor with alpha value of 1 and beta value of 0
         */
        AlphaBetaProcessing();

        /**
         * Applies alpha-beta correction to PGM images
         * @param src the source image
         * @param dst the modified image
         */
        void processImage(const PGMImage &src, PGMImage &dst) override;

        /**
         * Applies alpha-beta correction to PPM images
         * @param src the source image
         * @param dst the modified image
         */
        void processImage(const PPMImage &src, PPMImage &dst) override;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_ALPHABETAPROCESSING_H
