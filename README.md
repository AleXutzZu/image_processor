# imgproc

**imgproc** is a lightweight C++ image processing library that supports operations on grayscale (PGM) and color (PPM) images. It includes support for pixel-level manipulations, convolution filters (mean, Gaussian, Sobel), and drawing primitives like lines, circles, and filled rectangles.

## Features

- **PGM and PPM image loading and saving**
- **RGB and grayscale pixel classes**
- **Convolution filters**: mean blur, Gaussian blur, Sobel edge detection (horizontal and vertical)
- **Pixel-wise operations**: gamma correction, alpha-beta transformation
- **Drawing utilities**: line, circle, and rectangle rendering
- **Test suite** built using Google Test

## Namespace Organization

- `imgproc`: Core image processing types and logic
- `imgproc::draw`: Functions for geometric drawing (lines, circles, rectangles)


## Documentation

Full API documentation is generated using Doxygen. To build it locally:
```bash
cd lib
doxygen Doxyfile
```

You may also access the documentation online the on GitHub page of [this](https://alexutzzu.github.io/image_processor/) repository.

## Examples

Load and process an image:
```cpp
#include "image/PGMImage.h"
#include "image/processors/ConvolutionProcessing.h"
#include "image/processors/kernels/MeanBlurKernel.h"
imgproc::PGMImage input;
input.load("example.pgm");

imgproc::PGMImage output;
imgproc::MeanBlurKernel *kernel = new imgproc::MeanBlurKernel();
imgproc::ConvolutionProcessing processor(kernel);

processor.processImage(input, output);

output.save("blurred.pgm");
```

Draw a line on an image
```cpp
#include "image/PGMImage.h"
#include "geometry/drawing.h"

imgproc::PGMImage canvas(100, 100);
imgproc::draw::drawLine(canvas, imgproc::Point(10, 10), imgproc::Point(90, 90), imgproc::GrayPixel(255));
canvas.save("line.pgm");
```

## Other executables

In this repository you will also find 3 source files which can be compiled and provide a CLI for applying the various
operations implemented in this library.

For compiling them you will require Boost library's command_options component and the executables available are:

- `image_drawing` - enables the drawing functionality on PGM and PPM images supplied
- `pgm_editor` - accepts PGM images on which it can apply contrast, brightness, gamma adjustments and kernel convolutions
- `ppm_editor` - similar to `pgm_editor` but meant for PPM files
