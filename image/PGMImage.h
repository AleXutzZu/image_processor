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
    class PGMImage final : public Image<GrayPixel> {
    private:
        unsigned int maxGrayValue{};
    public:
        PGMImage();

        PGMImage(unsigned int width, unsigned int height);

        void load(const std::string &imagePath) override;

        void save(const std::string &imagePath) override;

        friend PGMImage operator+(float scalar, const PGMImage &vector);

        friend PGMImage operator*(float scalar, const PGMImage &vector);
    };


    class PGMImageProcessor : public virtual ImageProcessing<PGMImage> {
    };
}

#endif //IMAGE_PROCESSOR_PGMIMAGE_H
