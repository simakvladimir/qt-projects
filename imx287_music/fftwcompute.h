#ifndef FFTWCOMPUTE_H
#define FFTWCOMPUTE_H

#include "fftw/fftw3.h"
#include "buffer/safebuffer.h"

#include <QObject>
#include <QVector>

class FFTWCompute : public QObject
{
    Q_OBJECT
public:
    explicit FFTWCompute(QObject *parent = 0);
    
signals:
    
public slots:
    QVector<float> calculate_fftw(QVector<float> data);
    
};

#endif // FFTWCOMPUTE_H
