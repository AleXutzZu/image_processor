//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_PIXEL_H
#define IMAGE_PROCESSOR_PIXEL_H


#include <cstdint>
#include <ostream>

namespace imgproc {
    /**
     * Class representing a gray-scale valued pixel. Values are in range [0, 255]
     */
    class GrayPixel {
    private:
        uint8_t value;

    public:
        /**
         * Constructs a pixel with value 0
         */
        GrayPixel();
        /**
         * Constructs a pixel from the given value
         * @param value the value of the pixel
         */
        explicit GrayPixel(uint8_t value);
        /**
         * Adds two gray pixels together. The resulting value is clipped to be in the range [0, 255]
         * @param lhs the first pixel
         * @param rhs the second pixel
         * @return a new pixel with its value being the sum of the 2 pixels, clipped to the range [0, 255]
         */
        friend GrayPixel operator+(const GrayPixel &lhs, const GrayPixel &rhs);

        /**
         * Subtracts one gray pixel from the other. The resulting value is clipped to be in the range [0, 255]
         * @param lhs the pixel to subtract from
         * @param rhs the pixel to subtract
         * @return a new pixel with its value being the difference of the 2 pixels, clipped to the range [0, 255]
         */
        friend GrayPixel operator-(const GrayPixel &lhs, const GrayPixel &rhs);

        /**
         * Adds a scalar value to the pixel. The resulting value is truncated and clipped to be in the range [0, 255]
         * @param scalar the scalar to add to the pixel
         * @param vector the pixel to add the value to
         * @return a new pixel with the value described above
         */
        friend GrayPixel operator+(float scalar, const GrayPixel &vector);

        /**
         * Multiplies the value of the pixel by the scalar. The resulting value is truncated and clipped to be in the range
         * [0, 255]
         * @param scalar the scalar to multiply by
         * @param vector the pixel
         * @return a new pixel with the value described above
         */
        friend GrayPixel operator*(float scalar, const GrayPixel &vector);

        /**
         * Raises the value of the pixel to the power of the scalar value. The resulting value is truncated and clipped
         * to be in the range [0, 255]
         * @param scalar the scalar exponent
         * @param vector the pixel
         * @return a new pixel with the value described above
         */
        friend GrayPixel power(float scalar, const GrayPixel &vector);

        friend std::ostream &operator<<(std::ostream &os, const GrayPixel &pixel);

        /**
         * Returns the value contained in the pixel
         * @return the value
         */
        [[nodiscard]] uint8_t getValue() const;

        /**
         * Clips an integer value to the range [0, 255].
         * @param value the value to clip
         * @return the new clipped value
         */
        static uint8_t clip(int value);

        friend bool operator==(const GrayPixel &lhs, const GrayPixel &rhs);

        friend bool operator!=(const GrayPixel &lhs, const GrayPixel &rhs);
    };

    class RGBPixel {
    private:
        //0 - red; 1 - green; 2 - blue
        GrayPixel pixels[3]{};

    public:
        RGBPixel();

        inline friend RGBPixel operator+(const RGBPixel &lhs, const RGBPixel &rhs);
    };

} // imgproc

#endif //IMAGE_PROCESSOR_PIXEL_H
