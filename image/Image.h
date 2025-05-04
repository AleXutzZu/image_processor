//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_IMAGE_H
#define IMAGE_PROCESSOR_IMAGE_H

#include <stdexcept>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"

namespace imgproc {
    /**
     * Base class for representing an image.
     * @tparam T the type of data stored in the image (i.e the data type of the pixel)
     */
    template<typename T>
    class Image {
    protected:
        unsigned int width{};
        unsigned int height{};
        T **data{};

        [[nodiscard]] bool _valid(int x, int y) const;

        static void scalarAdd(float scalar, Image<T> &vector);

        static void scalarMultiply(float scalar, Image<T> &vector);

        void _deep_copy(const Image<T> &other);

        void zeroes(int w, int h);

    public:
        /**
         * Creates an empty image
         */
        Image() = default;

        /**
         * Constructs a blank image with the specified width and height
         * @param width the width of the image
         * @param height the height of the image
         */
        Image(unsigned int width, unsigned int height);

        virtual ~Image();

        /**
         * Loads the image at the specified path
         * @param imagePath the path to the image
         */
        virtual void load(const std::string &imagePath) = 0;

        /**
         * Saves the current image to disk
         * @param imagePath the path to save the image to
         */
        virtual void save(const std::string &imagePath) = 0;

        /**
         * Get a reference to the pixel at coordinates (x, y) in the image
         * @param x the x-coordinate of the pixel
         * @param y the y-coordinate of the pixel
         * @return the pixel at coordinates (x, y) in the image
         * @throws out_of_range if the coordinates are invalid
         */
        T &at(unsigned int x, unsigned int y);

        /**
         * Get a constant reference to the pixel at coordinates (x, y) in the image
         * @param x the x-coordinate of the pixel
         * @param y the y-coordinate of the pixel
         * @return the pixel at coordinates (x, y) in the image
         * @throws out_of_range if the coordinates are invalid
         */
        const T &cat(unsigned int x, unsigned int y) const;

        /**
         * Get a reference to the pixel at a point in the image
         * @param p the point of coordinates x and y
         * @return the pixel at point @a p in the image
         * @throws out_of_range if the coordinates are invalid
         */
        T &at(const Point &p);

        /**
         * Checks if the image is empty (i.e it has no pixels)
         * @return true if the image is empty, false otherwise
         */
        [[nodiscard]] bool isEmpty() const {
            return data != nullptr;
        }

        /**
         * Get a reference to an entire row of pixels in the image
         * @param y the row to return
         * @return an array with size equal to the width of the image
         * @throws out_of_range if the row is invalid
         */
        T *row(int y);

        /***
         * Get a rectangle of interest as an image
         * @param roiImg the image to store the ROI into
         * @param roiRect the bounds of the rectangle
         * @throws invalid_argument if the rectangle is not within the bounds of the image
         */
        void getROI(Image<T> &roiImg, const Rectangle &roiRect);

        /**
         * Get a rectangle of interest as an image
         * @param roiImg the image to store the ROI into
         * @param x the x-coordinate of the top-left corner of the rectangle
         * @param y the y-coordinate of the top-left corner of the rectangle
         * @param w the width of the rectangle
         * @param h the height of the rectangle
         * @throws invalid_argument if the rectangle is not within the bounds of the image
         */
        void getROI(Image<T> &roiImg, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

        /**
         * Deletes all data stored in the image and sets the width and height to 0
         */
        void release();

        /**
         * Returns the width of the image
         * @return the width
         */
        [[nodiscard]] unsigned int getWidth() const;

        /**
         * Returns the height of the image
         * @return the height
         */
        [[nodiscard]] unsigned int getHeight() const;
    };

    template<typename T>
    unsigned int Image<T>::getHeight() const {
        return height;
    }

    template<typename T>
    unsigned int Image<T>::getWidth() const {
        return width;
    }

    template<typename T>
    void Image<T>::release() {
        if (data != nullptr) {
            for (int i = 0; i < height; ++i) delete[] data[i];
            delete[] data;
            width = height = 0;
        }
    }

    template<typename T>
    void Image<T>::getROI(Image<T> &roiImg, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        Rectangle rectangle(x, y, w, h);
        getROI(roiImg, rectangle);
    }

    template<typename T>
    void Image<T>::getROI(Image<T> &roiImg, const Rectangle &roiRect) {
        if (roiRect.getX() + roiRect.getWidth() > width || roiRect.getY() + roiRect.getHeight() > height) {
            throw std::invalid_argument("Rectangle is not within the bounds of the image!");
        }
        roiImg.zeroes(roiRect.getWidth(), roiRect.getHeight());
        for (int i = 0; i < roiRect.getWidth(); ++i) {
            for (int j = 0; j < roiRect.getHeight(); ++j) {
                roiImg.at(i, j) = this->at(roiRect.getX() + i, roiRect.getY() + j);
            }
        }
    }

    template<typename T>
    T *Image<T>::row(int y) {
        if (!_valid(0, y)) throw std::out_of_range("Supplied coordinate is out of range");
        return data[y];
    }

    template<typename T>
    T &Image<T>::at(const Point &p) {
        return at(p.getX(), p.getY());
    }

    template<typename T>
    const T &Image<T>::cat(unsigned int x, unsigned int y) const {
        if (!_valid(x, y)) throw std::out_of_range("Supplied coordinates are out of range");

        return data[y][x];
    }

    template<typename T>
    T &Image<T>::at(unsigned int x, unsigned int y) {
        if (!_valid(x, y)) throw std::out_of_range("Supplied coordinates are out of range");

        return data[y][x];
    }

    template<typename T>
    Image<T>::~Image() {
        release();
    }

    template<typename T>
    Image<T>::Image(unsigned int width, unsigned int height) : width(width), height(height) {
        if (height > 0) data = new T *[height];

        for (unsigned int i = 0; i < height; ++i) {
            if (width > 0) data[i] = new T[width]();
        }
    }

    template<typename T>
    void Image<T>::zeroes(int w, int h) {
        release();
        if (w == 0 || h == 0) {
            width = height = 0;
            return;
        }
        width = w;
        height = h;
        data = new T *[height];
        for (int i = 0; i < height; ++i) {
            data[i] = new T[width];
        }
    }

    template<typename T>
    void Image<T>::_deep_copy(const Image<T> &other) {
        data = new T *[height];
        for (unsigned int i = 0; i < height; ++i) {
            data[i] = new T[width];
            for (unsigned int j = 0; j < width; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    template<typename T>
    void Image<T>::scalarMultiply(float scalar, Image<T> &vector) {
        for (unsigned int i = 0; i < vector.height; ++i) {
            for (unsigned int j = 0; j < vector.width; ++j) vector.data[i][j] = scalar * vector.data[i][j];
        }
    }

    template<typename T>
    void Image<T>::scalarAdd(float scalar, Image<T> &vector) {
        for (unsigned int i = 0; i < vector.height; ++i) {
            for (unsigned int j = 0; j < vector.width; ++j) vector.data[i][j] = scalar + vector.data[i][j];
        }
    }

    template<typename T>
    bool Image<T>::_valid(int x, int y) const {
        return 0 <= x && x < width && 0 <= y && y < height;
    }
}

#endif //IMAGE_PROCESSOR_IMAGE_H
