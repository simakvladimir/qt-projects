#include "model.h"


Model::Model(QObject *parent) :
    QObject(parent),
    enumMap(initEnums()),
    soundFile(NULL),
    fourier(NULL),
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
    if (soundFile)
        delete soundFile;

    soundFile = new WavFile;
    connect(soundFile, SIGNAL(samplesReaded(int)), this, SLOT(slotReadFileProgress(int)));
    soundFile->openWavFile(name.toLatin1().data());

    emit signalReadFileFinished(soundFile->getError(),soundFile->getErrorDesc());
}

void Model::slotInit(int devType)
{
    if (devType >= DEV_MAX){
        emit signalProcessFinished(0, "Не определенный тип устройства");
        return;
    }

    if (fourier)
        delete fourier;

    switch (devType) {
        case DEV_GPU_OPENCL:
        case DEV_CPU_OPENCL:
            fourier = new OclDft;
            dynamic_cast<OclDft*>(fourier)->setDevType(devType);
            qDebug() << "OPENCL";
            break;
        case DEV_CPU_X86:
            fourier = new Dft;
            qDebug() << "CPU";
            break;
        default:
            emit signalProcessFinished(1, "Неверный тип устройства");
            return;
    }

    if(!fourier->init()){
        emit signalProcessFinished(1, fourier->getErrorDescription());
        return;
    }

    emit signalInitFinished(0, QString("Устройство %1 инициализировано успешно.").arg(enumMap[devType]));
}

void Model::slotProcess(int winSize, int ch)
{
    Q_UNUSED(ch);

    if (!soundFile || !fourier)
        return;

    int Md = soundFile->getNumSamples() / winSize; // time
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

    soundFile->reset();

    QTime timeStart;
    timeStart = QTime::currentTime();

    while(soundFile->ifMoreDataAvailable()){

        in[sample].x = soundFile->readCurrentInput();
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
           }

            window++;
            emit signalProcessProgress( (window * 100) / Md );



        }
    }

    QTime finishTime = QTime::currentTime();
    timeDuration = QTime(0,0).addMSecs(timeStart.msecsTo(finishTime) );

    emit signalDataUpdated(Nd,Md);
    emit signalProcessFinished(0, "Спектр получен");

    delete in;
    delete out;

}

void Model::slotReadFileProgress(int value)
{
    emit signalReadProgress(value);
}

QStringList Model::getDeviceInfo()
{
    return fourier->getDeviceInfoList();
}
