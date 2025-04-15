//
// Created by AleXutzZu on 14/04/2025.
//

#ifndef IMAGE_PROCESSOR_KERNEL_H
#define IMAGE_PROCESSOR_KERNEL_H

namespace imgproc {

    class Kernel {
    protected:
        unsigned int width{};
        unsigned int height{};

        int **data{};

        [[nodiscard]] bool _valid(int i, int j) const;

    public:
        Kernel(unsigned int width, unsigned int height);

        virtual ~Kernel();

        [[nodiscard]] const int &at(int i, int j) const;

        [[nodiscard]] unsigned int getWidth() const;

        [[nodiscard]] unsigned int getHeight() const;
    };

} // imgproc

#endif //IMAGE_PROCESSOR_KERNEL_H
