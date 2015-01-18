#include "c_avx.h"

#include <immintrin.h> // avx
#include <intrin.h>

#include <cpuid.h>


/*!
 * \brief isAvxSupportedByCpu
 * \return
 */
int is_avx_supported_by_cpu() {
    int cpuInfo[4];
    __cpuid( 0, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3] );
    if( cpuInfo[0] != 0 ) {
        __cpuid( 1, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3] );
        return cpuInfo[2] & (bit_AVX | bit_OSXSAVE);
    } else {
        return 0;
    }
}

int convolve_avx_simple(float* in, float* out, int length,
        float* kernel, int kernel_length)
{
    float kernel_block[4] __attribute__ ((aligned (16)));

    __m128 kernel_reverse[kernel_length] __attribute__ ((aligned (16)));
    __m128 data_block __attribute__ ((aligned (16)));

    __m128 prod __attribute__ ((aligned (16)));
    __m128 acc __attribute__ ((aligned (16)));

    // Reverse the kernel and repeat each value across a 4-vector
    for(int i=0; i<kernel_length; i++){
        kernel_block[0] = kernel[kernel_length - i - 1];
        kernel_block[1] = kernel[kernel_length - i - 1];
        kernel_block[2] = kernel[kernel_length - i - 1];
        kernel_block[3] = kernel[kernel_length - i - 1];

        kernel_reverse[i] = _mm_load_ps(kernel_block);
    }

    for(int i=0; i<length-kernel_length; i+=4){

        // Zero the accumulator
        acc = _mm_setzero_ps();

        /* After this loop, we have computed 4 output samples
         * for the price of one.
         * */
        for(int k=0; k<kernel_length; k++){

            // Load 4-float data block. These needs to be an unaliged
            // load (_mm_loadu_ps) as we step one sample at a time.
            data_block = _mm_loadu_ps(in + i + k);
            prod = _mm_mul_ps(kernel_reverse[k], data_block);

            // Accumulate the 4 parallel values
            acc = _mm_add_ps(acc, prod);
        }
        _mm_storeu_ps(out+i, acc);

    }

    // Need to do the last value as a special case
    int i = length - kernel_length;
    out[i] = 0.0;
    for(int k=0; k<kernel_length; k++){
        out[i] += in[i+k] * kernel[kernel_length - k - 1];
    }

    return 0;
}


//#define KERNEL_LENGTH 1024
#define ALIGNMENT 32
#define AVX_SIMD_LENGTH 8
#define SSE_SIMD_LENGTH 4
#define VECTOR_LENGTH 16
int convolve_avx_unrolled_vector(float* in, float* out,
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

    for(int i=0; i<length-kernel_length; i+=VECTOR_LENGTH){

        acc0 = _mm256_setzero_ps();
        acc1 = _mm256_setzero_ps();

        for(int k=0; k<kernel_length; k+=VECTOR_LENGTH){

            int data_offset = i + k;

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
        _mm256_storeu_ps(out+i, acc0);
        _mm256_storeu_ps(out+i+AVX_SIMD_LENGTH, acc1);

    }

    // Need to do the last value as a special case
    int i = length - kernel_length;
    out[i] = 0.0;
    for(int k=0; k<kernel_length; k++){
        out[i] += in_aligned[0][i+k] * kernel[kernel_length - k - 1];
    }

    return 0;
}
