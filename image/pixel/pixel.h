//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_PIXEL_H
#define IMAGE_PROCESSOR_PIXEL_H


#include <cstdint>

namespace imgproc {

    class GrayPixel {
    private:
        uint8_t value;

    public:
        GrayPixel();

        explicit GrayPixel(uint8_t value);

        inline friend GrayPixel operator+(const GrayPixel &lhs, const GrayPixel &rhs);
        inline friend GrayPixel operator-(const GrayPixel &lhs, const GrayPixel &rhs);
    };

    class RGBPixel {
    private:
        uint8_t red, green, blue;

    public:
        RGBPixel();

        RGBPixel(uint8_t red, uint8_t green, uint8_t blue);

        inline friend RGBPixel operator+(const RGBPixel &lhs, const RGBPixel &rhs);
    };

} // imgproc

#endif //IMAGE_PROCESSOR_PIXEL_H
