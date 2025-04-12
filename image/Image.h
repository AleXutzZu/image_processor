//
// Created by AleXutzZu on 12/04/2025.
//

#ifndef IMAGE_PROCESSOR_IMAGE_H
#define IMAGE_PROCESSOR_IMAGE_H

#include <stdexcept>
#include "../point/Point.h"

namespace imgproc {
    template<typename T>
    class Image {
    protected:
        unsigned int width{};
        unsigned int height{};
        T **data{};

        bool _valid(int x, int y) {
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

        T &at(const Point &p) {
            return at(p.getX(), p.getY());
        }

        friend Image operator+(const Image<T> &lhs, const Image<T> &rhs) {
            if (lhs.height != rhs.height || lhs.width != rhs.width)
                throw std::runtime_error("Image sizes do not match");

            Image<T> result(lhs);

            for (int i = 0; i < result.height; ++i) {
                for (int j = 0; j < result.width; ++j) {
                    result.data[i][j] = result.data[i][j] + rhs.data[i][j];
                }
            }

            return result;
        }

        friend Image operator-(const Image<T> &lhs, const Image<T> &rhs) {
            if (lhs.height != rhs.height || lhs.width != rhs.width)
                throw std::runtime_error("Image sizes do not match");
            //TODO
        }
        //TODO operations * + - between a scalar and the image

        friend Image operator*(float scalar, const Image<T> &vector) {
            Image result = vector;

            for (unsigned int i = 0; i < result.height; ++i) {
                for (unsigned int j = 0; j < result.width; ++j) result.data[i][j] = scalar * result.data[i][j];
            }

            return result;
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
