#include "model.h"


Model::Model(QObject *parent) :
    QObject(parent),
    wavFile(NULL),
    Xd(NULL),
    Yd(NULL),
    Zd(NULL)
{
}

void Model::getModelData(double **_Xd, double **_Yd, double **_Zd)
{
    *_Xd = Xd;
    *_Yd = Yd;
    *_Zd = Zd;
}

void Model::slotReadFile(QString name)
{
    wavFile = new WavFile;
    wavFile->openWavFile(name.toLatin1().data());

    emit signalReadFileFinished(wavFile->getError(),wavFile->getErrorDesc());
}

void Model::slotProcess(int winSize, int devType, int ch)
{
    switch (devType) {
    case DEV_GPU:
        fourier = new OclDft;
        break;
    case DEV_CPU:

    default:
        emit signalProcessFinished(1, "Неверный тип устройства");
        return;
    }


    if(!fourier->init()){
        emit signalProcessFinished(1, fourier->getErrorDescription());
        return;
    }

    int Md = wavFile->getNumSamples() / winSize; // time
    int Nd = winSize / 2;// freq

    if (Xd)
        delete Xd;
    if (Yd)
        delete Yd;
    if (Zd)
        delete Zd;

    Xd = (double *)malloc(Nd*sizeof(double));
    Yd = (double *)malloc(Md*sizeof(double));
    Zd = (double *)malloc(Md*Nd*sizeof(double));

    cl_float2 *in = (cl_float2*)malloc( sizeof(cl_float2)*winSize );
    cl_float2 *out = (cl_float2*)malloc( sizeof(cl_float2)*winSize );

    int sample = 0;
    int window = 0;

    double hx = 3./(Nd-1);
    double hy = 6./(Md-1);

    for (int n = 0; n < Nd; n++)
        Xd[n] = -1.5 + n*hx;
    for (int m = 0; m < Md; m++)
        Yd[m] = -3 + m*hy;

    while(wavFile->ifMoreDataAvailable()){

        in[sample].x = wavFile->readCurrentInput();
        in[sample].y = 0;

        ++sample;

        if (sample >= winSize){

            sample = 0;

            if (!fourier->calculate(in, out, winSize, 1))
            {
                emit signalProcessFinished(1, fourier->getErrorDescription());
                return;
            }
            Zd[window*Nd] = 0;
            for (int i=1; i < Nd; i++){
                Zd[window*Nd+i] = out[i].x / 10000000;
//                qDebug() << Zd[window*Nd+i]  << " " <<  window*Nd+i;
            }

            window++;


        }
    }

    emit signalDataUpdated(Nd,Md);

    delete in;
    delete out;


    float iMax = Zd[0]; //set min and max as the first element
    int ind = 0;
    for (int i=4096; i < 6144; i++)
    {
        qDebug() << Zd[i] << " " <<  i << " !!!";
        if (Zd[i] > iMax){
            iMax = Zd[i];
            ind  = i;
        }
    }
    qDebug() << "Max" << iMax  << " " << ind;

}
