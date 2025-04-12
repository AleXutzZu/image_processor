//
// Created by AleXutzZu on 12/04/2025.
//

#include <fstream>
#include <iostream>
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
            throw std::runtime_error("invalid PGM header");
        }

        data = new uint8_t *[height];
        for (int i = 0; i < height; ++i) {
            data[i] = new uint8_t[width];
            for (int j = 0; j < width; ++j) {
                int d;
                input >> d;

                if (d < 0 || d > maxGrayValue) throw std::runtime_error("Invalid pixel data");

                data[i][j] = static_cast<uint8_t>(d);
            }
        }
    }

    void PGMImage::save(const std::string &imagePath) {

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

    PGMImage::PGMImage() = default;
}