//
// Created by AleXutzZu on 22/04/2025.
//

#include "HorizontalSobelKernel.h"

namespace imgproc {
    HorizontalSobelKernel::HorizontalSobelKernel() {
        data[0][0] = data[0][2] = 1;
        data[2][0] = data[2][2] = -1;
        data[0][1] = 2;
        data[2][1] = -2;
    }
} // imgproc