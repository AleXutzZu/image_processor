//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_PPMIMAGE_H
#define IMAGE_PROCESSOR_PPMIMAGE_H

#include "Image.h"
#include "processors/ImageProcessing.h"
#include "pixel/pixel.h"

namespace imgproc {

    class PPMImage final : Image<RGBPixel> {
        void load(const std::string &imagePath) override;

        void save(const std::string &imagePath) override;

    };

    class PPMImageProcessor : public virtual ImageProcessing<PPMImage> {
    };

} // imgproc

#endif //IMAGE_PROCESSOR_PPMIMAGE_H
