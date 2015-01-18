#ifndef IFOURIERTRANSFORM_H
#define IFOURIERTRANSFORM_H

#include <CL/cl.h>
#include <QString>
#include <QStringList>

class IFourierTransform
{
public:
    IFourierTransform() {};
    virtual ~IFourierTransform() {};

    virtual bool init() = 0;

    virtual bool calculate(
        const cl_float2 *in, // complex values input (packed real and imaginary)
        cl_float2 *out,      // complex values output
        int length,       // number of input and output values
        int sign
    ) = 0;

    virtual QString getErrorDescription() = 0;
    QStringList &getDeviceInfoList() { return deviceInfo; };

protected:
    QStringList deviceInfo;

};

#endif // IFOURIERTRANSFORM_H
