// Enable double-precision floating point numbers support.
// Not all platforms / devices support this, so you may have to switch to floats.
//#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#pragma OPENCL EXTENSION cl_intel_printf : enable
__kernel void dft(
        __global const float2 *in, // complex values input
        __global float2 *out,      // complex values output
        int lengthN,                // number of input and output values
        int sign)                  // sign modifier in the exponential :
                                   // 1 for forward transform, -1 for backward.
{
        // Get the varying parameter of the parallel execution :
        int i = get_global_id(0);

//        if (){
//            printf("!!!!!!!!!!!!! %d ", i);

//        }
        // In case we're executed "too much", check bounds :
        if (i >= lengthN)
                return;

//            printf("+ %f x%d ", in[i].x, i);
//            printf("- %f y%d", in[i].y, i);

        // Initialize sum and inner arguments
        float2 tot = 0;
        float param = (-2 * sign * i) * M_PI / (float)lengthN;

        for (int k = 0; k < lengthN; k++) {
                float2 value = in[k];

                // Compute sin and cos in a single call :
                float c;
                float s = sincos(k * param, &c);

                // This adds (value.x * c - value.y * s, value.x * s + value.y * c) to the sum :
                tot += (float2)(
                        dot(value, (float2)(c, -s)),
                        dot(value, (float2)(s, c))
                );
        }

//        if (sign == 1) {
//                // forward transform (space -> frequential)
         out[i] = (float2)( length(tot), 0.0f );

//        if (i==1){
//            printf("!!!!!!!!!!!!! %d ", i);
//            printf("| %f ", out[i].x);
//            printf("| %f ", out[i].y);
//        }
//        } else {
//                // backward transform (frequential -> space)
//                out[i] = tot / (double)length;
//        }
}
