//
// Created by AleXutzZu on 12/04/2025.
//

#include <fstream>
#include <sstream>
#include "PPMImage.h"

namespace imgproc {
    void PPMImage::load(const std::string &imagePath) {
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

        if (width <= 0 || height <= 0 || maxGray <= 0 || type != "P3") {
            throw std::runtime_error("Invalid PPM header");
        }

        this->width = width;
        this->height = height;
        this->maxGrayValue = maxGray;

        data = new RGBPixel *[height]();
        for (int i = 0; i < height; ++i) {
            data[i] = new RGBPixel[width];
            for (int j = 0; j < width; ++j) {
                int values[3];
                for (auto &pixel: values) {
                    if (!input.good()) throw std::runtime_error("Error whilst reading image data");
                    input >> pixel;
                    if (pixel < 0 || pixel > maxGray) throw std::runtime_error("Invalid pixel data");
                }

                data[i][j] = RGBPixel(values[0], values[1], values[2]);
            }
        }
    }

    void PPMImage::save(const std::string &imagePath) {
        std::ofstream output(imagePath);
        if (!output.is_open()) throw std::runtime_error("Cannot open file " + imagePath);

        output << "P3" << '\n';
        output << width << " " << height << "\n";
        output << maxGrayValue << '\n';
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) output << data[i][j] << " ";
            output << '\n';
        }
    }

    PPMImage::PPMImage(unsigned int width, unsigned int height) : Image(width, height) {}

    PPMImage operator+(float scalar, const PPMImage &vector) {
        PPMImage result = vector;
        PPMImage::scalarAdd(scalar, result);
        result.maxGrayValue = GrayPixel::clip(vector.maxGrayValue + scalar);
        return result;
    }

    PPMImage operator*(float scalar, const PPMImage &vector) {
        PPMImage result = vector;
        PPMImage::scalarMultiply(scalar, result);
        result.maxGrayValue = GrayPixel::clip(vector.maxGrayValue * scalar);
        return result;
    }

    PPMImage::PPMImage(const PPMImage &other) : Image<RGBPixel>(other) {
        maxGrayValue = other.maxGrayValue;
    }

    PPMImage &PPMImage::operator=(const PPMImage &other) {
        if (this != &other) {
            release();
            width = other.width;
            height = other.height;
            maxGrayValue = other.maxGrayValue;
            _deep_copy(other);
        }
        return *this;
    }

    void PPMImage::kernelConvolution(const Kernel &kernel, PPMImage &vector) {
        auto computeValueAtPixel = [&](int x, int y, int sample) -> GrayPixel {
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
                    switch (sample) {
                        case 0:
                            result += pixel.getRed().getValue() * kernel.at(i, j);
                            break;
                        case 1:
                            result += pixel.getGreen().getValue() * kernel.at(i, j);
                            break;
                        case 2:
                            result += pixel.getBlue().getValue() * kernel.at(i, j);
                            break;
                        default:
                            break;
                    }
                }
            }
            auto scaled = kernel.getScalingFunction()(result);
            return scaled;
        };

        for (int i = 0; i < vector.getHeight(); ++i) {
            for (int j = 0; j < vector.getWidth(); ++j) {
                GrayPixel pixels[3];
                for (int sample = 0; sample < 3; ++sample) {
                    pixels[sample] = computeValueAtPixel(j, i, sample);
                    vector.maxGrayValue = std::max(vector.maxGrayValue, (unsigned int) pixels[sample].getValue());
                }
                vector.at(j, i) = RGBPixel(pixels[0].getValue(), pixels[1].getValue(), pixels[2].getValue());
            }
        }
    }

    PPMImage operator*(const Kernel &kernel, const PPMImage &vector) {
        PPMImage result = vector;
        PPMImage::kernelConvolution(kernel, result);
        return result;
    }

    PPMImage::PPMImage() = default;
} // imgproc