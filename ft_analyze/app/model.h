#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QThread>
#include <QMap>
#include <QTime>

#include "wavfile.h"
#include "../host/ifouriertransform.h"
#include "../host/ocldft.h"
#include "../host/dft.h"

class Model : public QObject
{
    Q_OBJECT
public:

    enum{
        DEV_GPU_OPENCL,
        DEV_CPU_OPENCL,
        DEV_CPU_X86,

        DEV_MAX
    };

    explicit Model(QObject *parent = 0);

    void getModelData(double **_Xd, double **_Yd, double **_Zd);
    int getSamples()   { return soundFile ? soundFile->getNumSamples() : 0; }
    int getFetchFreq() { return soundFile ? soundFile->getSampleRateHz() : 0;  }
    QString getTimeDuration() { return timeDuration.toString("hh:mm:ss.zzz"); }
signals:
    void signalReadFileFinished(int,QString);
    void signalInitFinished(int, QString);
    void signalProcessFinished(int, QString);
    void signalDataUpdated(int, int);
    void signalReadProgress(int);
    void signalProcessProgress(int);

private slots:

public slots:
    void slotReadFile(QString name);
    void slotInit(int devType);
    void slotProcess(int winSize, int ch);
    void slotReadFileProgress(int value);

    QStringList getDeviceInfo();

    static QMap<int, QString> initEnums() {
        QMap<int, QString> map;
        map.insert(DEV_GPU_OPENCL,"GPU OCL");
        map.insert(DEV_CPU_OPENCL,"CPU OCL");
        map.insert(DEV_CPU_X86,"CPU x86");
        return map;
    }

private:
    QMap<int, QString> enumMap;

    QString fileName;

    WavFile *soundFile;
    IFourierTransform *fourier;

    double *Xd;
    double *Yd;
    double *Zd;

    QTime timeDuration;

    int error;
    QString errorDesc;
};

#endif // MODEL_H
