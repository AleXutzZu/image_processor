//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_PGMIMAGE_H
#define IMAGE_PROCESSOR_PGMIMAGE_H

#include <cstdint>
#include "Image.h"
#include "processors/ImageProcessing.h"
#include "pixel/pixel.h"

namespace imgproc {
    /**
     * Class representing an image following the PGM format
     */
    class PGMImage final : public Image<GrayPixel> {
    private:
        unsigned int maxGrayValue{};
    public:
        PGMImage();

        PGMImage(unsigned int width, unsigned int height);

        void load(const std::string &imagePath) override;

        void save(const std::string &imagePath) override;

        /**
         * Adds the scalar value to all the pixels in the image
         * @param scalar the scalar to add
         * @param vector the image to add the scalar to
         * @return a new PGM image with the computed values for pixels
         */
        friend PGMImage operator+(float scalar, const PGMImage &vector);

        /**
         * Multiplies all the pixels in the image by the scalar value
         * @param scalar the scalar to multiply by
         * @param vector the the image to have the scalar applied to
         * @return a new PGM image with the computed values for pixels
         */
        friend PGMImage operator*(float scalar, const PGMImage &vector);
    };

    /**
     * Base class for image processors applicable to PGM images
     */
    class PGMImageProcessor : public virtual ImageProcessing<PGMImage> {
    };
}

#endif //IMAGE_PROCESSOR_PGMIMAGE_H
