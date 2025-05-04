//
// Created by AleXutzZu on 14/04/2025.
//

#ifndef IMAGE_PROCESSOR_KERNEL_H
#define IMAGE_PROCESSOR_KERNEL_H

#include <functional>
#include "../../pixel/pixel.h"

namespace imgproc {
    /**
     * Abstract class representing a kernel used for convolution operations
     */
    class Kernel {
    protected:
        unsigned int width{};
        unsigned int height{};
        std::function<GrayPixel(int)> scalingFunction;
        int **data{};

        [[nodiscard]] bool _valid(int i, int j) const;

    public:
        /**
         * Constructs a matrix filled with the value 0 with the specified width and height and a scaling function
         * @param width the width of the matrix
         * @param height the height of the matrix
         * @param function the scale function applied to the result
         */
        Kernel(unsigned int width, unsigned int height, const std::function<GrayPixel(int)> &function);

        virtual ~Kernel();

        /**
         * Returns the value at position (i, j) in the matrix
         * @param i the row
         * @param j the column
         * @return the value at row i and column j in the matrix
         * @throws out_of_range if the coordinates are invalid
         */
        [[nodiscard]] const int &at(int i, int j) const;

        /**
         * Returns the width of the matrix
         * @return the width
         */
        [[nodiscard]] unsigned int getWidth() const;

        /**
         * Returns the height of the matrix
         * @return the height
         */
        [[nodiscard]] unsigned int getHeight() const;

        /**
         * Returns the scaling function which should be used on the kernel after applying it on a set of pixels
         * @return the scaling function
         */
        [[nodiscard]] const std::function<GrayPixel(int)> &getScalingFunction() const;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_KERNEL_H
