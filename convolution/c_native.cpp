#include "c_native.h"

int convolve_naive(float* in,     float* out, int length,
                   float* kernel, int kernel_length)
{
    for(int i=0; i<=length-kernel_length; i++){

        out[i] = 0.0;
        for(int k=0; k<kernel_length; k++){
            out[i] += in[i+k] * kernel[kernel_length - k - 1];
        }
    }

    return 0;
}
