#include "image_proc.h"

//TASK 2.1
#ifdef TODO_IMAGE_PROCESS_COLOR_POINT
void image_proc_process_color_point(Matrix(Color)* source,  Matrix(int)* result, <complete-this>){
    matrix_free(*result);

    result->cols = source->cols;
    result->rows = source->rows;
    result->array = new_arr(int, result->cols*result->rows);

    for(int i=0; i<source->rows; i++){
        for(int j=0; j<source->cols; j++){
            _xsub(*result, i, j) = f((_xsub(*source, i, j)).R,  + (_xsub(*source, i, j)).G,  (_xsub(*source, i, j)).B);
        }
    }
}
#endif

int grayscale(int R, int G, int B){
   //Complete this
}

void image_proc_get_grayscale(Matrix(Color)* source,  Matrix(int)* result){
    #ifdef TODO_IMAGE_PROCESS_COLOR_POINT
    image_proc_process_color_point(source, result, <complete-this>);
    #endif
}


void image_proc_light_dark(Matrix(int)* mat, int threshold){
    int pixels = mat->rows * mat->cols;
    for(int i=0; i<pixels; i++){
        mat->array[i] = mat->array[i] < threshold ? 0 : 1;
    }
}

//TASK 2.2 
#define _vsub(__M, _i, _j) (matrix_check_not_overflow((__M), (_i), (_j)) ? _xsub(__M, _i, _j) : 0)

void image_proc_opening_filter(Matrix(int)* mat){
    
    //write the code for erosion filter here


    //write the code for dilation filter here

}

int image_proc_coords_accumulate(Matrix(int) mat, int (*f) (int, int)){
    int sum = 0;
    for(int i=0; i<mat.rows; i++){
        for(int j=0; j<mat.cols; j++){
            if(_sub(mat, i, j)==1)
                sum += f(i, j);
        }
    }
    return sum;
}

//TASK 2.3
int _xx(int x, int y){
    return 0; //Edit this
}

int _x(int x, int y){
    return 0; //Edit this
}

int _y(int x, int y){
    return 0; //Edit this
}

int _xy(int x, int y){
    return 0; //Edit this
}

int counter(int x, int y){
    return 1; //This is done
}

LineData image_proc_linreg(Matrix(int) mat){
    double sum_x2 =  image_proc_coords_accumulate(mat, _xx);
    double sum_xy =  image_proc_coords_accumulate(mat, _xy);
    double sum_y = image_proc_coords_accumulate(mat, _y);
    double sum_x = image_proc_coords_accumulate(mat, _x);
    double count = image_proc_coords_accumulate(mat, counter);

    LineData res;
    double S_xx = sum_x2 - (sum_x*sum_x)/count;
    double S_xy = sum_xy - (sum_x*sum_y)/count;

    res.b = S_xy/S_xx;
    res.a = sum_y/count - res.b * sum_x/count;

    return res;

}

void image_proc_draw_line(Matrix(int)* mat, LineData ld){
    for(int i=0; i<mat->cols; i++){
        int y = ld.a + ld.b * i;
        if(matrix_check_not_overflow(*mat, i, y))
            _xsub(*mat, i, y) = -1; 
    }
}

//TASK 2.4
PolyData image_proc_polyreg(Matrix(int) mat){
    double count = image_proc_coords_accumulate(mat, counter);

    double* xarr = new_arr(double, count*4);
    double* yarr = new_arr(double, count);


    int k = 0;
    for(int i=0; i<mat.rows; i++){
        for(int j=0; j<mat.cols; j++){
            if(_sub(mat, i, j)==1){
                xarr[4*k] = 1;
                xarr[4*k+1] = i;
                xarr[4*k+2] = i*i;
                xarr[4*k+3] = i*i*i;
                yarr[k] = j;
                k++;
            }
        }
    }

    Matrix(double) A;
    A.cols = 4; A.rows = count; A.array = xarr;
    Matrix(double) b;
    b.cols = 1; b.rows = count; b.array = yarr;

    matrix_all(double, a, 4, 1, -1);
    //continue from here
    //you can add more matrices, if needed



    PolyData poly = {
        .a0 = a.array[0],
        .a1 = a.array[1],
        .a2 = a.array[2],
        .a3 = a.array[3],
    };

    matrix_free(A);
    matrix_free(b);

    //free necessary matrices here

    //free necessary matrices here

    return poly;

}

void image_proc_draw_poly(Matrix(int)* mat, PolyData pd){
    for(int i=0; i<mat->cols; i++){
        int y = pd.a0 + pd.a1 * i + pd.a2 * i * i + pd.a3 * i * i * i;
        if(matrix_check_not_overflow(*mat, i, y))
            _xsub(*mat, i, y) = -1; 
    }
}