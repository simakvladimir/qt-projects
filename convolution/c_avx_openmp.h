#ifndef C_AVX_OPENMP_H
#define C_AVX_OPENMP_H

int convolve_avx_unrolled_vector_openmp(float* in, float* out,
        int length, float* kernel, int kernel_length);


#endif // C_AVX_OPENMP_H
