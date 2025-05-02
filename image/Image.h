//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_IMAGE_H
#define IMAGE_PROCESSOR_IMAGE_H

#include <stdexcept>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"

namespace imgproc {
    template<typename T>
    class Image {
    protected:
        unsigned int width{};
        unsigned int height{};
        T **data{};

        [[nodiscard]] bool _valid(int x, int y) const {
            return 0 <= x && x < width && 0 <= y && y < height;
        }

        static void scalarAdd(float scalar, Image<T> &vector) {
            for (unsigned int i = 0; i < vector.height; ++i) {
                for (unsigned int j = 0; j < vector.width; ++j) vector.data[i][j] = scalar + vector.data[i][j];
            }
        }

        static void scalarMultiply(float scalar, Image<T> &vector) {
            for (unsigned int i = 0; i < vector.height; ++i) {
                for (unsigned int j = 0; j < vector.width; ++j) vector.data[i][j] = scalar * vector.data[i][j];
            }
        }

        void _deep_copy(const Image<T> &other) {
            data = new T *[height];
            for (unsigned int i = 0; i < height; ++i) {
                data[i] = new T[width];
                for (unsigned int j = 0; j < width; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }

        void zeroes(int w, int h) {
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

    public:

        Image() = default;

        Image(unsigned int width, unsigned int height) : width(width), height(height) {}

        Image(const Image<T> &other) {
            width = other.width;
            height = other.height;

            _deep_copy(other);
        }

        virtual ~Image() {
            release();
        }

        virtual void load(const std::string &imagePath) = 0;

        virtual void save(const std::string &imagePath) = 0;

        T &at(unsigned int x, unsigned int y) {
            if (!_valid(x, y)) throw std::out_of_range("Supplied coordinates are out of range");

            return data[y][x];
        }

        const T &cat(unsigned int x, unsigned int y) const {
            if (!_valid(x, y)) throw std::out_of_range("Supplied coordinates are out of range");

            return data[y][x];
        }

        T &at(const Point &p) {
            return at(p.getX(), p.getY());
        }

        [[nodiscard]] bool isEmpty() const {
            return data != nullptr;
        }

        T *row(int y) {
            return data[y];
        }

        Image &operator=(const Image<T> &other) {
            if (this != &other) {
                release();
                height = other.height;
                width = other.width;

                _deep_copy(other);
            }
            return *this;
        }

        void getROI(Image<T> &roiImg, const Rectangle &roiRect) {
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

        void getROI(Image<T> &roiImg, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
            Rectangle rectangle(x, y, w, h);
            getROI(roiImg, rectangle);
        }

        void release() {
            if (data != nullptr) {
                for (int i = 0; i < height; ++i) delete[] data[i];
            }
        }

        [[nodiscard]] unsigned int getWidth() const {
            return width;
        }

        [[nodiscard]] unsigned int getHeight() const {
            return height;
        }
    };
}

#endif //IMAGE_PROCESSOR_IMAGE_H
