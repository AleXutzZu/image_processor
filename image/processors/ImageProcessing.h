//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_IMAGEPROCESSING_H
#define IMAGE_PROCESSOR_IMAGEPROCESSING_H

#include "../Image.h"

namespace imgproc {
    template<typename T>
    class ImageProcessing {
    public:
        virtual void processImage(const T &src, T &dst) = 0;

        virtual ~ImageProcessing() = default;
    };
}
#endif //IMAGE_PROCESSOR_IMAGEPROCESSING_H
