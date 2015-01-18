#include <QCoreApplication>
#include <QTime>
#include <QDebug>

#include "c_native.h"
#include "c_avx.h"
#include "c_avx_openmp.h"
#include "open_cl.h"

enum TestID{
  C_NATIVE,
  C_AVX,
  C_AVX_OPENMP,
  OPEN_CL_CPU,
  OPEN_CL_GPU
};

static int start_test(TestID id,
                      int data_block_size,
                      int coef_block_size)
{
    int dataWidth = data_block_size;
    int coefWidth = coef_block_size;

    float *inData   = new float[dataWidth];
    float *coefData = new float[coefWidth];;
    float *outData  = new float[dataWidth];

    for (int i = 0; i < dataWidth; i++){
        inData[i] = -1 + ( qrand() % 3 );
    }

    for (int i = 0; i < coefWidth; i++){
        coefData[i] = 0.1 * ( qrand() % 5 );
    }

    OpenCl openCl;
    if (id == OPEN_CL_CPU)
        openCl.init(OpenCl::CPU);

    if (id == OPEN_CL_GPU)
        openCl.init(OpenCl::GPU);

    QTime startTime = QTime::currentTime();

    int total_time_msec;
    int index;
    for (index=1;;index++){

        switch (id) {
        case C_NATIVE:
            convolve_naive(inData, outData, dataWidth, coefData, coefWidth);
            break;
        case C_AVX:
        case C_AVX_OPENMP:
            if (is_avx_supported_by_cpu()){
                if (id==C_AVX)
                    convolve_avx_unrolled_vector(inData, outData, dataWidth, coefData, coefWidth);
                if (id==C_AVX_OPENMP)
                    convolve_avx_unrolled_vector_openmp(inData, outData, dataWidth, coefData, coefWidth);

            } else {
                qDebug() << "AVX not supported by your cpu. Test failed.";
                return 0;
            }
            break;
        case OPEN_CL_GPU:
        case OPEN_CL_CPU:
            if (!openCl.run(inData,coefData,outData,dataWidth,coefWidth)){
                return 0;
            }
            break;
        default:
            break;


        }


        total_time_msec = startTime.msecsTo(QTime::currentTime());
        if (total_time_msec > 1000){
            break;
        }

    }
//    qDebug() << total_time_msec;
    return (index * dataWidth / (float)total_time_msec)*1000;
}


int main(int argc, char *argv[])
{
    int data_length = 32000;
    int coef_length = 1024;

    qDebug() << "   Convolution test. ";
    qDebug() << " Data block = " << data_length << ", coef block = " << coef_length << ".";

    qDebug() << "1. C_NATIVE. Sample rate = "<< start_test(C_NATIVE, data_length, coef_length) << " samples/s";
    qDebug() << "2. C_AVX. Sample rate = "<< start_test(C_AVX, data_length, coef_length) << " samples/s";
    qDebug() << "3. C_AVX+OPENMP. Sample rate = "<< start_test(C_AVX_OPENMP, data_length, coef_length) << " samples/s";

    qDebug() << "4. OPEN_CL_CPU. Sample rate = "<< start_test(OPEN_CL_CPU, data_length, coef_length) << " samples/s";
    qDebug() << "5. OPEN_CL_GPU. Sample rate = "<< start_test(OPEN_CL_GPU, data_length, coef_length) << " samples/s";

    return 0;
}
