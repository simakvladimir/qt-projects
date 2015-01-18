#ifndef C_AVX_H
#define C_AVX_H

int is_avx_supported_by_cpu();

int convolve_avx_simple(float* in, float* out, int length,
        float* kernel, int kernel_length);
int convolve_avx_unrolled_vector(float* in, float* out,
        int length, float* kernel, int kernel_length);
#endif // C_AVX_H
