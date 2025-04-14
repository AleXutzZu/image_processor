//
// Created by AleXutzZu on 14/04/2025.
//

#include "IdentityKernel.h"

namespace imgproc {
    IdentityKernel::IdentityKernel() : Kernel(3, 3) {
        data = new int *[height];
        for (int i = 0; i < 3; ++i) {
            data[i] = new int[3];
            for (int j = 0; j < 3; ++j) data[i][j] = 0;
        }
        data[1][1] = 1;
    }
} // imgproc