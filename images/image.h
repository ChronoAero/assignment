#include "../lib/matrix.h"
#include "../lib/color.h"
#include "../lib/std.h"

#ifndef IMAGE_H
#define IMAGE_H

    #ifndef MATRIX_COLOR
    #define MATRIX_COLOR
        define_matrix(Color);
    #endif

    void get_image1(Matrix(Color)*);
    void get_image2(Matrix(Color)*);

#endif