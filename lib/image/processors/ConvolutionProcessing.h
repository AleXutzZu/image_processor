//
// Created by AleXutzZu on 14/04/2025.
//

#ifndef IMAGE_PROCESSOR_CONVOLUTIONPROCESSING_H
#define IMAGE_PROCESSOR_CONVOLUTIONPROCESSING_H

#include "../PGMImage.h"
#include "../PPMImage.h"
#include "kernels/Kernel.h"
#include <functional>

namespace imgproc {
    /**
     * Processor responsible for applying a kernel convolution on the PPM and PGM image formats
     */
    class ConvolutionProcessing : public PGMImageProcessor, public PPMImageProcessor {
    private:
        Kernel *kernel;

    public:
        /**
         * Constructs a default no-op processor with the identity kernel
         */
        ConvolutionProcessing();

        /**
         * Constructs a processor with the given kernel. This constructor takes full ownership of the deletion
         * of the pointer to the kernel so it has to be heap allocated
         * @param kernel a heap allocated kernel that will be managed the processor for de-allocation
         */
        explicit ConvolutionProcessing(Kernel *kernel);

        /**
         * Applies kernel convolution to PPM images
         * @param src the source image
         * @param dst the modified image
         */
        void processImage(const PPMImage &src, PPMImage &dst) override;

        /**
         * Applies kernel convolution to PGM images
         * @param src the source image
         * @param dst the modified image
         */
        void processImage(const PGMImage &src, PGMImage &dst) override;

        ~ConvolutionProcessing() override;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_CONVOLUTIONPROCESSING_H
