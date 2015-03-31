#include "fftw_thread.h"
#include <QDebug>

FFTW_Thread::FFTW_Thread(QObject *parent, SafeBuffer *buf) :
    QThread(parent),
    buffer( buf )
{
    start();
}


void FFTW_Thread::run()
{
    FFTWCompute *fftw_compute = new FFTWCompute();

    QVector<float> data;
    QVector<float> avr_data;

    int counter = 0;

    while (isRunning()){

        msleep( 10 );

        bool  isEmpty;
        float value;

        //  enter to critical section
        buffer->lock();

        if (buffer->is_empty()) {
            buffer->unlock();
            continue;
        }

        while( !buffer->is_empty() ){
            value = buffer->pop( &isEmpty );
            data.append( value );
        };

        //  exit from critical secction
        buffer->unlock();

        for (int index = 0; index < data.count(); index += 2 )
        {
            float avr_val = data.at( index );
            avr_val += data.at( index + 1 );
            avr_val /= 2;

            avr_data.append( avr_val );
        }
        QVector<float> result = fftw_compute->calculate_fftw( avr_data );

        result.remove( 0 );

        emit fftw_complete( result );

        avr_data.clear();
        data.clear();

    }
}
