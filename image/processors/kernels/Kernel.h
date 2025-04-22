//
// Created by AleXutzZu on 14/04/2025.
//

#ifndef IMAGE_PROCESSOR_KERNEL_H
#define IMAGE_PROCESSOR_KERNEL_H

#include <functional>
#include "../../pixel/pixel.h"

namespace imgproc {

    class Kernel {
    protected:
        unsigned int width{};
        unsigned int height{};
        std::function<GrayPixel(int)> scalingFunction;
        int **data{};

        [[nodiscard]] bool _valid(int i, int j) const;

    public:

        Kernel(unsigned int width, unsigned int height, const std::function<GrayPixel(int)> &function);

        virtual ~Kernel();

        [[nodiscard]] const int &at(int i, int j) const;

        [[nodiscard]] unsigned int getWidth() const;

        [[nodiscard]] unsigned int getHeight() const;

        [[nodiscard]] const std::function<GrayPixel(int)> &getScalingFunction() const;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_KERNEL_H
