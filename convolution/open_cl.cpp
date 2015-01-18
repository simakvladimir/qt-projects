#include "open_cl.h"


OpenCl::OpenCl()
{

}

bool OpenCl::init(Dev type)
{
    bool success;

    success = loadOpenCLSrc("OpenCl.cl");
    if (!success)
        return false;

    success = getIntelId();
    if (!success)
        return false;

    success = initOpenClEnvironment(type);
    if (!success)
        return false;

    success = getDeviceInfo();
    if (!success)
        return false;

    success = initOpenClProgram();
    if (!success)
        return false;

    return true;
}

bool OpenCl::run(float *in, float *coef, float *out, int inWidth, int coefWidth)
{
    cl_int ret;

    /* Create Memory Buffer */
    input  = clCreateBuffer(context, CL_MEM_READ_ONLY  | CL_MEM_USE_HOST_PTR, inWidth * sizeof(float), (void*)in, &ret);
    coefficients = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, coefWidth * sizeof(float), coef, &ret);
    output  = clCreateBuffer(context, CL_MEM_WRITE_ONLY  | CL_MEM_USE_HOST_PTR, inWidth * sizeof(float), (void*)out, &ret);

    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::run]" << "Memory is not be allocated";
        return false;
    }

    /* Set OpenCL Kernel Parameters */
    ret  = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&input);
    ret |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&coefficients);
    ret |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&output);
    ret |= clSetKernelArg(kernel, 3, sizeof(int), (void *)&inWidth);
    ret |= clSetKernelArg(kernel, 4, sizeof(int), (void *)&coefWidth);
    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::run]" << "Kernel parameters are not be applied";
        return false;
    }

    /* Execute OpenCL Kernel */
    size_t globalWorkSize = (inWidth - coefWidth) / 8;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&globalWorkSize, NULL, 0, NULL, NULL);
    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::run]" << "Kernel is failed while executing";
        return false;
    }

    ret = clFinish(command_queue);

    /* Copy results from the memory buffer */
    ret = clEnqueueReadBuffer(command_queue, output, CL_TRUE, 0,
                              inWidth * sizeof(float), out, 0, NULL, NULL);

    int i = inWidth - coefWidth;
    out[i] = 0.0;
    for(int k=0; k<coefWidth; k++){
        out[i] += in[i+k] * coef[coefWidth - k - 1];
    }

    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::run]" << "Result can't be readed";
        return false;
    }

    return true;
}

bool OpenCl::getIntelId()
{
    cl_int ret;
    cl_uint        ret_num_platforms;
    cl_uint        ret_num_devices;


    intel_platform_id = getIntelOCLPlatform();
    if  ( NULL == intel_platform_id ){
        qDebug() << "[OpenCl::getIntelId]" << "Intel devices are not founded";
        return false;
    }

    return true;
}

cl_platform_id OpenCl::getIntelOCLPlatform()
{
    cl_platform_id pPlatforms[10] = { 0 };
    char pPlatformName[128] = { 0 };

    cl_uint uiPlatformsCount = 0;
    cl_int err = clGetPlatformIDs(10, pPlatforms, &uiPlatformsCount);
    for (cl_uint ui = 0; ui < uiPlatformsCount; ++ui)
    {
        err = clGetPlatformInfo(pPlatforms[ui], CL_PLATFORM_NAME, 128 * sizeof(char), pPlatformName, NULL);
        if ( err != CL_SUCCESS )
        {
            return NULL;
        }
        /*
         * AMD Accelerated Parallel Processing
         * Intel(R) OpenCL
         */

        if (!strcmp(pPlatformName, "AMD Accelerated Parallel Processing")){
            qDebug() << "Platform name = " << pPlatformName;
            return pPlatforms[ui];
        }
    }

    return NULL;
}

bool OpenCl::getDeviceInfo()
{
    cl_int ret;

    int num_cores;
    ret = clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &num_cores, NULL);
    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::getDeviceInfo]" << "Option info is not geted";
        return false;
    }

    int max_freq;
    ret = clGetDeviceInfo(device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &max_freq, NULL);
    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::getDeviceInfo]" << "Option info is not geted";
        return false;
    }

    char pDeviceName[128] = { 0 };
    ret = clGetDeviceInfo(device_id, CL_DEVICE_NAME, 128, &pDeviceName, NULL);
    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::getDeviceInfo]" << "Option info is not geted";
        return false;
    }
//    QSdeviceName = QString(pDeviceName);

    QStringList deviceInfo;
    deviceInfo << QString("%1").arg(pDeviceName)
               << QString("%1").arg(QString::number(max_freq))
               << QString("%1").arg(num_cores);

    qDebug() << deviceInfo;

    return true;
}

bool OpenCl::loadOpenCLSrc(const char *fileName)
{
    FILE *fp;

    if (sourceStr)
        free(sourceStr);

    fp = fopen(fileName, "r");
    if (!fp) {
        qDebug() << "[OpenCl::loadOpenCLSrc]" << "Kernel is not able to be opened";
        return false;
    }
    sourceStr = (char*)malloc(MAX_SOURCE_SIZE);
    sourceSize = fread(sourceStr, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    return true;
}

bool OpenCl::initOpenClEnvironment(Dev dev)
{
    cl_int ret;

    /* Create OpenCL context */
    cl_context_properties context_properties[3] = {CL_CONTEXT_PLATFORM, (cl_context_properties)intel_platform_id, NULL };
    context = clCreateContextFromType(context_properties,  dev /* CL_DEVICE_TYPE_GPU */, NULL, NULL, NULL);

    size_t cb;
    cl_device_id devices[16];

    ret = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &cb);
    ret = clGetContextInfo(context, CL_CONTEXT_DEVICES, cb, devices, NULL);
    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::initOpenClEnvironment]" << "Impossible to create context";
        return false;
    }

    device_id = devices[0];


    /* Create Command Queue */
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::initOpenClEnvironment]" << "Can't create queue";
        return false;
    }

    return true;
}

bool OpenCl::initOpenClProgram()
{
    cl_int ret;

    /* Create Kernel Program from the source */
    program = clCreateProgramWithSource(context, 1, (const char **)&sourceStr,
                                       (const size_t *)&sourceSize, &ret);
    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::initOpenClProgram]" << "Impossible to create OpenCl programm";
        return false;
    }

    /* Build Kernel Program */
    ret = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
   if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::initOpenClProgram]" << "Impossible to compile OpenCl kernel";
        size_t len;
        char *buffer;
        buffer = (char*)calloc(10240,sizeof(char));
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 10240*sizeof(char), buffer, &len);
        qDebug() << "[OpenCl::initOpenClProgram] Build Log: " << buffer;
        return false;
    }

    /* Create OpenCL Kernel */
    kernel = clCreateKernel(program, "convolve", &ret);
    if (CL_SUCCESS != ret){
        qDebug() << "[OpenCl::initOpenClProgram]" << "Impossible to create OpenCl kernel";
        return false;
    }

    return true;
}
