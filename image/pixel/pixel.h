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

        static uint8_t clip(int value);

    public:
        GrayPixel();

        explicit GrayPixel(uint8_t value);

        inline friend GrayPixel operator+(const GrayPixel &lhs, const GrayPixel &rhs);

        inline friend GrayPixel operator-(const GrayPixel &lhs, const GrayPixel &rhs);

        inline friend GrayPixel operator+(float scalar, const GrayPixel &vector);

        inline friend GrayPixel operator*(float scalar, const GrayPixel &vector);
    };

    class RGBPixel {
    private:
        GrayPixel red, green, blue;

    public:
        RGBPixel();

        inline friend RGBPixel operator+(const RGBPixel &lhs, const RGBPixel &rhs);
    };

} // imgproc

#endif //IMAGE_PROCESSOR_PIXEL_H
