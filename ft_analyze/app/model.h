#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QThread>

#include "wavfile.h"
#include "../host/ifouriertransform.h"
#include "../host/ocldft.h"

class Model : public QObject
{
    Q_OBJECT
public:

    enum{
       DEV_GPU,
       DEV_CPU
    };

    explicit Model(QObject *parent = 0);

    void getModelData(double **_Xd, double **_Yd, double **_Zd);

signals:
    void signalReadFileFinished(int,QString);
    void signalProcessFinished(int, QString);
    void signalDataUpdated(int, int);

private slots:

public slots:
    void slotReadFile(QString name);
    void slotProcess(int winSize, int devType, int ch);

private:
    QString fileName;

    WavFile *wavFile;
    IFourierTransform *fourier;


    double *Xd;
    double *Yd;
    double * Zd;

    int error;
    QString errorDesc;
};

#endif // MODEL_H
