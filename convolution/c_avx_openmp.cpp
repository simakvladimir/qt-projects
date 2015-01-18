#include "c_avx_openmp.h"
#include <immintrin.h> // avx
#include <intrin.h>

#define ALIGNMENT 32
#define AVX_SIMD_LENGTH 8
#define SSE_SIMD_LENGTH 4
#define VECTOR_LENGTH 16
int convolve_avx_unrolled_vector_openmp(float* in, float* out,
        int length, float* kernel, int kernel_length)
{
    float kernel_block[AVX_SIMD_LENGTH] __attribute__ (
            (aligned (ALIGNMENT)));
    float in_aligned[AVX_SIMD_LENGTH][length] __attribute__ (
            (aligned (ALIGNMENT)));

    __m256 kernel_reverse[kernel_length] __attribute__ (
            (aligned (ALIGNMENT)));
    __m256 data_block __attribute__ ((aligned (ALIGNMENT)));

    __m256 prod __attribute__ ((aligned (ALIGNMENT)));
    __m256 acc0 __attribute__ ((aligned (ALIGNMENT)));
    __m256 acc1 __attribute__ ((aligned (ALIGNMENT)));

    // Repeat the kernel across the vector
    for(int i=0; i<kernel_length; i++){
        for(int j=0; j<AVX_SIMD_LENGTH; j++){
            kernel_block[j] = kernel[kernel_length - i - 1];
        }

        kernel_reverse[i] = _mm256_load_ps(kernel_block);
    }

    /* Create a set of 4 aligned arrays
     * Each array is offset by one sample from the one before
     */
    for(int i=0; i < SSE_SIMD_LENGTH; i++){
        memcpy(in_aligned[i], (in+i), (length-i)*sizeof(float));
    }

    int index;
    #pragma omp parallel for default(none) private(index, acc0,acc1,prod,data_block) shared(kernel_length,length,in_aligned,kernel_reverse,out)
    for(index=0; index<length-kernel_length; index+=VECTOR_LENGTH){

        acc0 = _mm256_setzero_ps();
        acc1 = _mm256_setzero_ps();

        for(int k=0; k<kernel_length; k+=VECTOR_LENGTH){

            int data_offset = index + k;

            for (int l = 0; l < SSE_SIMD_LENGTH; l++){

                for (int m = 0; m < VECTOR_LENGTH; m+=SSE_SIMD_LENGTH) {

                    data_block = _mm256_loadu_ps(
                            in_aligned[l] + data_offset + m);
                    prod = _mm256_mul_ps(kernel_reverse[k+l+m], data_block);

                    acc0 = _mm256_add_ps(acc0, prod);

                    data_block = _mm256_loadu_ps(in_aligned[l] + data_offset
                            + m + AVX_SIMD_LENGTH);
                    prod = _mm256_mul_ps(kernel_reverse[k+l+m], data_block);

                    acc1 = _mm256_add_ps(acc1, prod);

                }
            }
        }
        _mm256_storeu_ps(out+index, acc0);
        _mm256_storeu_ps(out+index+AVX_SIMD_LENGTH, acc1);

    }

    // Need to do the last value as a special case
    int i = length - kernel_length;
    out[i] = 0.0;
    for(int k=0; k<kernel_length; k++){
        out[i] += in_aligned[0][i+k] * kernel[kernel_length - k - 1];
    }

    return 0;
}
