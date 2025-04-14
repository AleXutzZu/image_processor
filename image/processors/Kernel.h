//
// Created by AleXutzZu on 14/04/2025.
//

#ifndef IMAGE_PROCESSOR_KERNEL_H
#define IMAGE_PROCESSOR_KERNEL_H

namespace imgproc {

    class Kernel {
    private:
        unsigned int width{};
        unsigned int height{};

        unsigned int **data;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_KERNEL_H
