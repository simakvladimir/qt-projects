__kernel void convolve(
      __global const float * input,
    __constant const float * coefficients,
    __write_only  __global float * output,
    const int inputWidth,
    const int coefficientsWidth
)
{

    int i;
    int x = get_global_id(0);

    float8 outData   = (float8)(0.0);

    for(i = 0; i < coefficientsWidth; i++){
        float8 data = vload8(x, (__global float*)input+i);
        float8 prod = (float8)(coefficients[coefficientsWidth-i-1]);
        outData += data * prod;
    }
    vstore8(outData, x, (__global float*)output);
}
