//
// Created by AleXutzZu on 11/05/2025.
//
#include <boost/program_options.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include "image/PPMImage.h"
#include "image/PGMImage.h"
#include "geometry/drawing.h"

namespace po = boost::program_options;

bool is_ppm(const std::string &path) {
    return std::filesystem::path(path).extension() == ".ppm";
}

bool is_pgm(const std::string &path) {
    return std::filesystem::path(path).extension() == ".pgm";
}

int main(int argc, char *argv[]) {
    try {
        std::string file_path;
        std::string shape;
        std::vector<unsigned int> center, p1, p2, tl;
        unsigned int r = 0, w = 0, h = 0;
        unsigned int col = 0, red = 0, green = 0, blue = 0;

        po::options_description generic("Allowed options");
        generic.add_options()
                ("help,h", "produce help message")
                ("shape", po::value<std::string>(&shape)->required(), "Shape type: circle, line, rect")
                ("c", po::value<std::vector<unsigned int>>(&center)->multitoken(), "Center coordinates for circle")
                ("r", po::value<unsigned int>(&r), "Radius for circle")
                ("p1", po::value<std::vector<unsigned int>>(&p1)->multitoken(), "Start point for line")
                ("p2", po::value<std::vector<unsigned int>>(&p2)->multitoken(), "End point for line")
                ("tl", po::value<std::vector<unsigned int>>(&tl)->multitoken(), "Top-left point for rectangle")
                ("w", po::value<unsigned int>(&w), "Width of rectangle")
                ("h", po::value<unsigned int>(&h), "Height of rectangle")
                ("col", po::value<unsigned int>(&col)->default_value(0), "Gray color for PGM (0-255)")
                ("red", po::value<unsigned int>(&red)->default_value(0), "Red component for PPM (0-255)")
                ("green", po::value<unsigned int>(&green)->default_value(0), "Green component for PPM (0-255)")
                ("blue", po::value<unsigned int>(&blue)->default_value(0), "Blue component for PPM (0-255)");

        po::options_description hidden("Hidden options");
        hidden.add_options()
                ("file", po::value<std::string>(&file_path)->required(), "Input image file (PPM or PGM)");

        po::positional_options_description p;
        p.add("file", 1);

        po::options_description all("All options");
        all.add(generic).add(hidden);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(all).positional(p).run(), vm);

        if (vm.count("help")) {
            std::cout
                    << "Usage: image_drawing <file_path> --shape <circle|line|rect> [shape options] [color options]\n";
            std::cout << generic << "\n";
            return 0;
        }

        po::notify(vm);

        // Validate file extension
        if (!is_ppm(file_path) && !is_pgm(file_path)) {
            throw std::runtime_error("file_path must have extension .ppm or .pgm");
        }

        // Validate shape and required shape-specific args
        if (shape == "circle") {
            if (center.size() != 2 || !vm.count("r")) {
                throw std::runtime_error("Circle requires --c <x y> and --r <radius>");
            }
        } else if (shape == "line") {
            if (p1.size() != 2 || p2.size() != 2) {
                throw std::runtime_error("Line requires --p1 <x y> and --p2 <x y>");
            }
        } else if (shape == "rect") {
            if (tl.size() != 2 || !vm.count("w") || !vm.count("h")) {
                throw std::runtime_error("Rect requires --tl <x y>, --w <width>, and --h <height>");
            }
        } else {
            throw std::runtime_error("Shape must be one of: circle, line, rect");
        }

        // Validate color
        if (is_pgm(file_path)) {
            if (col > 255) throw std::runtime_error("PGM col must be between 0 and 255");
        } else {
            if (red > 255 || green > 255 || blue > 255) {
                throw std::runtime_error("RGB values must be in range 0-255");
            }
        }

        if (is_pgm(file_path)) {
            imgproc::PGMImage image;
            image.load(file_path);

            const imgproc::GrayPixel &color = imgproc::GrayPixel(col);
            if (shape == "circle") {
                unsigned int x = center[0], y = center[1];
                imgproc::Point center_point(x, y);
                imgproc::draw::drawCircle(image, center_point, r, color);

            } else if (shape == "line") {
                unsigned int x1 = p1[0], y1 = p1[1];
                unsigned int x2 = p2[0], y2 = p2[1];

                imgproc::Point point1(x1, y1), point2(x2, y2);
                imgproc::draw::drawLine(image, point1, point2, color);
            } else if (shape == "rect") {
                unsigned int x = tl[0], y = tl[1];
                imgproc::Rectangle rectangle(x, y, w, h);

                imgproc::draw::drawRectangle(image, rectangle, color);
            }
            image.save(file_path);
            std::cout << "Saved modified PGM image to: " << file_path;
        } else {
            imgproc::PPMImage image;
            image.load(file_path);

            const imgproc::RGBPixel &color = imgproc::RGBPixel(red, green, blue);
            if (shape == "circle") {
                unsigned int x = center[0], y = center[1];
                imgproc::Point center_point(x, y);
                imgproc::draw::drawCircle(image, center_point, r, color);

            } else if (shape == "line") {
                unsigned int x1 = p1[0], y1 = p1[1];
                unsigned int x2 = p2[0], y2 = p2[1];

                imgproc::Point point1(x1, y1), point2(x2, y2);
                imgproc::draw::drawLine(image, point1, point2, color);
            } else if (shape == "rect") {
                unsigned int x = tl[0], y = tl[1];
                imgproc::Rectangle rectangle(x, y, w, h);

                imgproc::draw::drawRectangle(image, rectangle, color);
            }
            image.save(file_path);
            std::cout << "Saved modified PPM image to: " << file_path;
        }


    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
