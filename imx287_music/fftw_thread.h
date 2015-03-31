#ifndef FFTW_THREAD_H
#define FFTW_THREAD_H

#include <QThread>
#include "fftwcompute.h"
#include "buffer/safebuffer.h"
#include "buffer/common.h"

class FFTW_Thread : public QThread
{
    Q_OBJECT
private:
    SafeBuffer *buffer;
public:
    explicit FFTW_Thread(QObject *parent = 0, SafeBuffer *buf = 0);

    void run();
    
signals:
    void fftw_complete( const MyArray &bb );
    
public slots:
    
};

#endif // FFTW_THREAD_H
