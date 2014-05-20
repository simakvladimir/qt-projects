#ifndef IFOURIERTRANSFORM_H
#define IFOURIERTRANSFORM_H

#include <CL/cl.h>

class IFourierTransform
{
public:
    IFourierTransform() {};

    virtual bool calculate(
        const cl_float2 *in, // complex values input (packed real and imaginary)
        cl_float2 *out,      // complex values output
        int length,       // number of input and output values
        int sign
    ) = 0;
};

#endif // IFOURIERTRANSFORM_H
