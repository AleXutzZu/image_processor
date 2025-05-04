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
        /**
         * Creates a pixel with all RGB values set to 0
         */
        RGBPixel();

        /**
         * Creates a pixel with the given RGB values
         * @param red the red value
         * @param green the green value
         * @param blue the blue value
         */
        RGBPixel(uint8_t red, uint8_t green, uint8_t blue);

        /**
         * Adds two RGB pixels together by adding each RGB value. Each result is clipped to be in the range [0, 255]
         * @param lhs the first pixel
         * @param rhs the second pixel
         * @return an RGB pixel with the new values
         */
        friend RGBPixel operator+(const RGBPixel &lhs, const RGBPixel &rhs);

        /**
         * Subtracts the second RGB pixel from the first one for each RGB value. Each result is clipped to be in the range
         * [0, 255]
         * @param lhs the first pixel
         * @param rhs the second pixel
         * @return an RGB pixel with the new values
         */
        friend RGBPixel operator-(const RGBPixel &lhs, const RGBPixel &rhs);

        /**
         * Adds a scalar value to each component of the RGB pixel. Each result is truncated and clipped to be in the range [0, 255]
         * @param scalar the scalar to add
         * @param vector the pixel to add the scalar to
         * @return an RGB pixel with the new values
         */
        friend RGBPixel operator+(float scalar, const RGBPixel &vector);

        /**
         * Multiplies each component of the RGB pixel by the scalar value. Each result is truncated and clipped to be in the range
         * [0, 255]
         * @param scalar the scalar to multiply by
         * @param vector the pixel to be multiplied
         * @return an RGB pixel with the new values
         */
        friend RGBPixel operator*(float scalar, const RGBPixel &vector);

        /**
         * Raises each component of the RGB pixel to the power of the scalar value. Each result is truncated and clipped
         * to be in the range [0, 255]
         * @param scalar the scalar exponent
         * @param vector the RGB pixel
         * @return an RGB pixel with the new values
         */
        friend RGBPixel power(float scalar, const RGBPixel &vector);

        friend std::ostream& operator<<(std::ostream &os, const RGBPixel &pixel);

        /**
         * Returns the red component of the RGB pixel
         * @return the red value as a GrayPixel
         */
        [[nodiscard]] GrayPixel getRed() const;

        /**
         * Returns the green component of the RGB pixel
         * @return the green value as a GrayPixel
         */
        [[nodiscard]] GrayPixel getGreen() const;

        /**
         * Returns the blue component of the RGB pixel
         * @return the blue value as a GrayPixel
         */
        [[nodiscard]] GrayPixel getBlue() const;

        friend bool operator==(const RGBPixel &lhs, const RGBPixel &rhs);

        friend bool operator!=(const RGBPixel &lhs, const RGBPixel &rhs);
    };

} // imgproc

#endif //IMAGE_PROCESSOR_PIXEL_H
