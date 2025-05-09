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
        /**
         * Constructs a completely empty PPM image with no width, height or pixel data
         */
        PPMImage();

        /**
         * Constructs a completely black PPM image with the given width and height
         * @param width the width of the image
         * @param height the height of the image
         */
        PPMImage(unsigned int width, unsigned int height);

        PPMImage(const PPMImage &other);

        void load(const std::string &imagePath) override;

        void save(const std::string &imagePath) override;

        /**
         * Adds the scalar value to all the pixels in the image
         * @param scalar the scalar to add
         * @param vector the image to add the scalar to
         * @return a new PPM image with the computed values for pixels
         */
        friend PPMImage operator+(float scalar, const PPMImage &vector);

        /**
         * Multiplies all the pixels in the image by the scalar value
         * @param scalar the scalar to multiply by
         * @param vector the the image to have the scalar applied to
         * @return a new PPM image with the computed values for pixels
         */
        friend PPMImage operator*(float scalar, const PPMImage &vector);

        /**
         * Applies a convolution kernel to the image
         * @param kernel the kernel to apply
         * @param vector the image
         * @return a new PPM image with the computed values for pixels
         */
        friend PPMImage operator*(const Kernel &kernel, const PPMImage &vector);

        /**
         * Raises all pixels to the power of the scalar value
         * @param scalar the scalar exponent
         * @param vector the image
         * @return a new PPM image with the computed values for pixels
         */
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
