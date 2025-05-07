//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_PPMIMAGE_H
#define IMAGE_PROCESSOR_PPMIMAGE_H

#include "Image.h"
#include "processors/ImageProcessing.h"
#include "pixel/pixel.h"
#include "processors/kernels/Kernel.h"

namespace imgproc {
    /**
     * Class representing an image following the PPM format
     */
    class PPMImage final : public Image<RGBPixel> {
    private:
        unsigned int maxGrayValue{};

        static void kernelConvolution(const Kernel &kernel, PPMImage &vector);

    public:
        PPMImage();

        PPMImage(unsigned int width, unsigned int height);

        PPMImage(const PPMImage &other);

        void load(const std::string &imagePath) override;

        void save(const std::string &imagePath) override;

        friend PPMImage operator+(float scalar, const PPMImage &vector);

        friend PPMImage operator*(float scalar, const PPMImage &vector);

        friend PPMImage operator*(const Kernel &kernel, const PPMImage &vector);

        friend PPMImage operator^(float scalar, const PPMImage &vector);

        PPMImage &operator=(const PPMImage &other);
    };

    /**
     * Base class for image processors applicable to PPM images
     */
    class PPMImageProcessor : public virtual ImageProcessing<PPMImage> {
    };

} // imgproc

#endif //IMAGE_PROCESSOR_PPMIMAGE_H
