#ifndef OCLDFT_H
#define OCLDFT_H

#include "ifouriertransform.h"
#include "utils.h"

#include <QObject>
#include <QDebug>


#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MEM_SIZE (4096)
#define MAX_SOURCE_SIZE (0x100000)

class OclDft : public QObject, public IFourierTransform
{
    Q_OBJECT
public:
    explicit OclDft(QObject *parent = 0);
    ~OclDft() {}
    
    bool calculate(const cl_float2 *in, // complex values input (packed real and imaginary)
        cl_float2 *out,      // complex values output
        int length,       // number of input and output values
        int sign
    );

    bool init();


    bool loadOpenCLSrc(const char *fileName);
    bool getPlatformInfo();
    bool initOpenClEnvironment();
    bool initOpenClProgram();

    bool releaseBuffers();


    void setErrorDescription(QString errorSrt) { error = errorSrt; }
    QString getErrorDescription() { return error; }

signals:
    
public slots:

private:
    char   *sourceStr;
    size_t  sourceSize;
    int     num_cores;
    cl_platform_id intel_platform_id;
    cl_device_id device_id;
    cl_context context;
    cl_command_queue command_queue;
    cl_program program;
    cl_kernel  kernel;

    cl_mem memVectorIn;
    cl_mem memVectorOut;

    QString error;
};

#endif // OCLDFT_H
