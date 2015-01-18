#include "ocldft.h"

OclDft::OclDft(QObject *parent) :
    QObject(parent),
    sourceStr(NULL),
    intel_platform_id(NULL),
    device_id(NULL),
    context(NULL),
    command_queue(NULL),
    program(NULL),
    kernel(NULL),
    memVectorIn(NULL),
    memVectorOut(NULL)
{
}

OclDft::~OclDft()
{
    clReleaseMemObject(memVectorIn);
    clReleaseMemObject(memVectorOut);

}

bool OclDft::calculate(const cl_float2 *in, cl_float2 *out, int length, int sign)
{
    cl_int ret;

    if (length > MEM_SIZE)
    {
        setErrorDescription("Большой размер массива.");
        return false;
    }

    /* Create Memory Buffer */
    memVectorIn   = clCreateBuffer(context,  CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, length * sizeof(cl_float2), (void*)in, &ret);
    memVectorOut = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, length * sizeof(cl_float2), out, &ret);
    if (CL_SUCCESS != ret){
        setErrorDescription("Невозможно выделить память.");
        return false;
    }

    if (CL_SUCCESS != ret){
        setErrorDescription("Невозможно записать входные данные.");
        return false;
    }

    /* Set OpenCL Kernel Parameters */
    ret  = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memVectorIn);
    ret |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&memVectorOut);
    ret |= clSetKernelArg(kernel, 2, sizeof(int), (void *)&length);
    ret |= clSetKernelArg(kernel, 3, sizeof(int), (void *)&sign);
    if (CL_SUCCESS != ret){
        setErrorDescription("Невозможно установить параметры ядра.");
        return false;
    }

    /* Execute OpenCL Kernel */
    size_t globalWorkSize = length;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&globalWorkSize, NULL, 0, NULL, NULL);
    if (CL_SUCCESS != ret){
        setErrorDescription("Ядро не выполнилось.");
        return false;
    }

    ret = clFinish(command_queue);

    /* Copy results from the memory buffer */
    cl_float2 temp[20];
    ret = clEnqueueReadBuffer(command_queue, memVectorOut, CL_TRUE, 0,
                              length * sizeof(cl_float2), out, 0, NULL, NULL);
    if (CL_SUCCESS != ret){
        setErrorDescription("Результат не может быть прочитан.");
        return false;
    }
    return true;
}

bool OclDft::init()
{
    bool success;

    success = loadOpenCLSrc("device/dft.cl");
    if (!success)
        return false;

    success = getIntelId();
    if (!success)
        return false;

    success = initOpenClEnvironment();
    if (!success)
        return false;

    success = getDeviceInfo();
    if (!success)
        return false;

    qDebug() << getDeviceInfoList();

    success = initOpenClProgram();
    if (!success)
        return false;

    return true;
}

/*!
 * \brief OclDft::loadOpenCLSrc Загрузка исходных кодов "ядра"
 * \param source Путь до cl файла
 * \return true в случае успеха
 */
bool OclDft::loadOpenCLSrc(const char *fileName)
{
    FILE *fp;

    if (sourceStr)
        free(sourceStr);

    fp = fopen(fileName, "r");
    if (!fp) {
        setErrorDescription("Невозможно открыть ядро");
        return false;
    }
    sourceStr = (char*)malloc(MAX_SOURCE_SIZE);
    sourceSize = fread(sourceStr, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    return true;
}

bool OclDft::getDeviceInfo()
{
    cl_int ret;

    deviceInfo.clear();

    int num_cores;
    ret = clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &num_cores, NULL);
    if (CL_SUCCESS != ret){
        setErrorDescription("Доп. инф-ция не может быть получена.");
        return false;
    }

    int max_freq;
    ret = clGetDeviceInfo(device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &max_freq, NULL);
    if (CL_SUCCESS != ret){
        setErrorDescription("Доп. инф-ция не может быть получена.");
        return false;
    }

    char pDeviceName[128] = { 0 };
    ret = clGetDeviceInfo(device_id, CL_DEVICE_NAME, 128, &pDeviceName, NULL);
    if (CL_SUCCESS != ret){
        setErrorDescription("Доп. инф-ция не может быть получена.");
        return false;
    }
    deviceName = QString(pDeviceName);


    deviceInfo << QString("%1").arg(deviceName)
               << QString("%1").arg(QString::number(max_freq))
               << QString("%1").arg(num_cores);

    return true;
}

/*!
 * \brief OclDft::getPlatformInfo Получение общей информации об оборудовании
 * \return
 */
bool OclDft::getIntelId()
{
    cl_int ret;
    cl_uint        ret_num_platforms;
    cl_uint        ret_num_devices;


    intel_platform_id = IntelUtils::getIntelOCLPlatform();
    if  ( NULL == intel_platform_id ){
        setErrorDescription("Intel устройства не найдены.");
        return false;
    }

    return true;
}


bool OclDft::initOpenClEnvironment()
{
    cl_int ret;

    /* Create OpenCL context */
    cl_context_properties context_properties[3] = {CL_CONTEXT_PLATFORM, (cl_context_properties)intel_platform_id, NULL };
    context = clCreateContextFromType(context_properties, devType ? CL_DEVICE_TYPE_CPU : CL_DEVICE_TYPE_GPU, NULL, NULL, NULL);

    size_t cb;
    cl_device_id devices[16];

    ret = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &cb);
    ret = clGetContextInfo(context, CL_CONTEXT_DEVICES, cb, devices, NULL);
    if (CL_SUCCESS != ret){
        setErrorDescription("Невозможно создать контекст.");
        return false;
    }

    device_id = devices[0];


    /* Create Command Queue */
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    if (CL_SUCCESS != ret){
        setErrorDescription("Невозможно создать очередь.");
        return false;
    }

    return true;
}

bool OclDft::initOpenClProgram()
{
    cl_int ret;

    /* Create Kernel Program from the source */
    program = clCreateProgramWithSource(context, 1, (const char **)&sourceStr,
                                       (const size_t *)&sourceSize, &ret);
    if (CL_SUCCESS != ret){
        setErrorDescription("Невозможно создать программу.");
        return false;
    }

    /* Build Kernel Program */
    ret = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
   if (CL_SUCCESS != ret){
        setErrorDescription("Невозможно скомпилировать ядро.");

        size_t len;
        char *buffer;
        buffer = (char*)calloc(10240,sizeof(char));
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 10240*sizeof(char), buffer, &len);
        qDebug() << "[OpenCl Build Log]" << buffer;
        return false;
    }

    /* Create OpenCL Kernel */
    kernel = clCreateKernel(program, "dft", &ret);
    if (CL_SUCCESS != ret){
        setErrorDescription("Невозможно создать ядро.");
        return false;
    }

    return true;
}
