//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_IMAGEPROCESSING_H
#define IMAGE_PROCESSOR_IMAGEPROCESSING_H

#include "../Image.h"

namespace imgproc {
    /**
     * Base interface for applying an operation on an image
     * @tparam T the type of image this processor applies to
     */
    template<typename T>
    class ImageProcessing {
    public:
        /**
         * Processes the image stored in @a src and stores the result in @a dst
         * @param src the image to process
         * @param dst the output image
         */
        virtual void processImage(const T &src, T &dst) = 0;

        virtual ~ImageProcessing() = default;
    };
}
#endif //IMAGE_PROCESSOR_IMAGEPROCESSING_H
