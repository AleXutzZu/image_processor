//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_PIXEL_H
#define IMAGE_PROCESSOR_PIXEL_H


#include <cstdint>
#include <ostream>

namespace imgproc {

    class GrayPixel {
    private:
        uint8_t value;

    public:

        GrayPixel();

        explicit GrayPixel(uint8_t value);

        friend GrayPixel operator+(const GrayPixel &lhs, const GrayPixel &rhs);

        friend GrayPixel operator-(const GrayPixel &lhs, const GrayPixel &rhs);

        friend GrayPixel operator+(float scalar, const GrayPixel &vector);

        friend GrayPixel operator*(float scalar, const GrayPixel &vector);

        friend GrayPixel power(float scalar, const GrayPixel &vector);

        friend std::ostream &operator<<(std::ostream &os, const GrayPixel &pixel);

        [[nodiscard]] uint8_t getValue() const;

        static uint8_t clip(int value);
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
