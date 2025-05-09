//
// Created by AleXutzZu on 12/04/2025.
//

#include <fstream>
#include <sstream>
#include "PGMImage.h"

namespace imgproc {
    void PGMImage::load(const std::string &imagePath) {
        std::ifstream input(imagePath);
        if (!input.is_open()) throw std::runtime_error("Cannot open file " + imagePath);

        release();

        std::string line;
        std::string header;

        std::string type;

        int width, height, maxGray;

        do {
            std::getline(input, line);
            if (!line.empty() && line[0] != '#') header += line + " ";

            std::stringstream stream(header);
            stream >> type >> width >> height >> maxGray;
            if (!stream.eof()) break;
            if (!input.good()) break;
        } while (true);

        if (width <= 0 || height <= 0 || maxGray <= 0 || type != "P2") {
            throw std::runtime_error("Invalid PGM header");
        }

        this->width = width;
        this->height = height;
        this->maxGrayValue = maxGray;

        data = new GrayPixel *[height]();
        for (int i = 0; i < height; ++i) {
            data[i] = new GrayPixel[width];
            for (int j = 0; j < width; ++j) {
                if (!input.good()) throw std::runtime_error("Error whilst reading image data");
                int d;
                input >> d;

                if (d < 0 || d > maxGray) throw std::runtime_error("Invalid pixel data");

                data[i][j] = GrayPixel(d);
            }
        }
    }

    void PGMImage::save(const std::string &imagePath) {
        std::ofstream output(imagePath);
        if (!output.is_open()) throw std::runtime_error("Cannot open file " + imagePath);

        output << "P2" << '\n';
        output << width << " " << height << "\n";
        output << maxGrayValue << '\n';
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) output << data[i][j] << " ";
            output << '\n';
        }
    }

    PGMImage::PGMImage(unsigned int width, unsigned int height) : Image(width, height) {}

    PGMImage operator+(float scalar, const PGMImage &vector) {
        PGMImage result = vector;
        PGMImage::scalarAdd(scalar, result);
        result.maxGrayValue = GrayPixel::clip(vector.maxGrayValue + scalar);
        return result;
    }

    PGMImage operator*(float scalar, const PGMImage &vector) {
        PGMImage result = vector;
        PGMImage::scalarMultiply(scalar, result);
        result.maxGrayValue = GrayPixel::clip(vector.maxGrayValue * scalar);
        return result;
    }

    PGMImage &PGMImage::operator=(const PGMImage &other) {
        if (this != &other) {
            release();
            width = other.width;
            height = other.height;
            maxGrayValue = other.maxGrayValue;
            _deep_copy(other);
        }
        return *this;
    }

    PGMImage::PGMImage(const PGMImage &other) : Image(other) {
        maxGrayValue = other.maxGrayValue;
    }

    void PGMImage::kernelConvolution(const Kernel &kernel, PGMImage &vector) {
        PGMImage result = vector;

        auto computeValueAtPixel = [&](int x, int y) -> GrayPixel {
            int result = 0;

            for (int i = 0; i < kernel.getHeight(); ++i) {
                for (int j = 0; j < kernel.getWidth(); ++j) {
                    int nx = x - j + kernel.getWidth() / 2;
                    int ny = y - i + kernel.getHeight() / 2;

                    nx = std::max(nx, 0);
                    nx = std::min<int>(nx, vector.getWidth() - 1);

                    ny = std::max(ny, 0);
                    ny = std::min<int>(ny, vector.getHeight() - 1);

                    auto pixel = vector.cat(nx, ny);
                    result += pixel.getValue() * kernel.at(i, j);
                }
            }
            auto scaled = kernel.getScalingFunction()(result);
            return scaled;
        };

        for (int i = 0; i < vector.getHeight(); ++i) {
            for (int j = 0; j < vector.getWidth(); ++j) {
                auto newPixelValue = computeValueAtPixel(j, i);
                result.at(j, i) = newPixelValue;
                result.maxGrayValue = std::max(result.maxGrayValue, (unsigned int) newPixelValue.getValue());
            }
        }
        vector = result;
    }

    PGMImage operator*(const Kernel &kernel, const PGMImage &vector) {
        PGMImage result = vector;
        PGMImage::kernelConvolution(kernel, result);
        return result;
    }

    PGMImage operator^(float scalar, const PGMImage &vector) {
        PGMImage result = vector;
        PGMImage::scalarPower(scalar, result);
        result.maxGrayValue = power(scalar, GrayPixel(result.maxGrayValue)).getValue();
        return result;
    }

    PGMImage::PGMImage() = default;
}