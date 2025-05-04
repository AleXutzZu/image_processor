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

        if (data != nullptr) release();

        std::string line;
        std::string header;

        std::string type;

        do {
            std::getline(input, line);
            if (!line.empty() && line[0] != '#') header += line + " ";

            std::stringstream stream(header);
            stream >> type >> width >> height >> maxGrayValue;
            if (!stream.eof()) break;
            if (!input.good()) break;
        } while (true);

        if (width <= 0 || height <= 0 || maxGrayValue <= 0 || type != "P2") {
            throw std::runtime_error("Invalid PGM header");
        }

        data = new GrayPixel *[height]();
        for (int i = 0; i < height; ++i) {
            data[i] = new GrayPixel[width];
            for (int j = 0; j < width; ++j) {
                if (!input.good()) throw std::runtime_error("Error whilst reading image data");
                int d;
                input >> d;

                if (d < 0 || d > maxGrayValue) throw std::runtime_error("Invalid pixel data");

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
        return result;
    }

    PGMImage operator*(float scalar, const PGMImage &vector) {
        PGMImage result = vector;
        PGMImage::scalarMultiply(scalar, result);
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

    PGMImage::PGMImage(const PGMImage &other)  : Image(other) {
        maxGrayValue = other.maxGrayValue;
    }

    PGMImage::PGMImage() = default;
}