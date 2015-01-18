#ifndef OPEN_CL_H
#define OPEN_CL_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


#include <QDebug>

#define MEM_SIZE (4096)
#define MAX_SOURCE_SIZE (0x100000)

class OpenCl
{



public:
    enum Dev{
        CPU = CL_DEVICE_TYPE_CPU,
        GPU = CL_DEVICE_TYPE_GPU
    };
    explicit OpenCl();

    bool init(Dev type);
    bool run(float *in,
             float *coef,
             float *out,
             int inWidth,
             int coefWidth);

signals:

public slots:


private:
    char          *sourceStr;
    size_t         sourceSize;

    cl_platform_id   intel_platform_id;
    cl_device_id     device_id;
    cl_context       context;
    cl_command_queue command_queue;

    cl_program program;
    cl_kernel  kernel;

    cl_mem input;
    cl_mem coefficients;
    cl_mem output;


    bool getIntelId();
    cl_platform_id getIntelOCLPlatform();
    bool getDeviceInfo();
    bool loadOpenCLSrc(const char *fileName);
    bool initOpenClEnvironment(Dev dev);
    bool initOpenClProgram();

};
#endif // OPEN_CL_H
