#include "bustthread.h"
#include <QDebug>

BustThread::BustThread(QObject *parent) :
    QThread(parent)
{
}

void BustThread::run()
{
    unsigned one_digit;
    QString value;
    qint64  i,j;
    quint64 k, length, half;
    quint64 sum_low_half, sum_high_half;

    counter = 0;

    for ( i=bottom; i<top; i++ ){

        sum_low_half  = sum_high_half = k = 0;

        value  = QString::number(i);
        length = value.length();

        half = digit >> 1;

        for( j=length-1; j>=0; j-- ){
            one_digit = value.at(j).toLatin1() - '0';
            if ( k++ < (half) )
                sum_high_half += one_digit;
            else
               sum_low_half   += one_digit;
        }

        if ( sum_low_half == sum_high_half )
            counter++;
    }
    emit thr_finish(counter);

//    qDebug() << this << counter.toUnsignedLong();
}
