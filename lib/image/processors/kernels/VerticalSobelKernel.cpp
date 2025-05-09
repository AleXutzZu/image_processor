//
// Created by AleXutzZu on 22/04/2025.
//

#include "VerticalSobelKernel.h"

namespace imgproc {
    VerticalSobelKernel::VerticalSobelKernel() {
        data[0][0] = data[2][0] = -1;
        data[0][2] = data[2][2] = 1;
        data[1][0] = -2;
        data[1][2] = 2;
    }
} // imgproc