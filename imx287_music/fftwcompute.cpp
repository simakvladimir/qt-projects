#include "fftwcompute.h"

#include <qmath.h>

#include <QDebug>


FFTWCompute::FFTWCompute(QObject *parent) :
    QObject(parent)
{
}


 QVector<float> FFTWCompute::calculate_fftw( QVector<float> data  ){

     QVector<float> out_vector;

    fftw_complex *in, *out;
    fftw_plan p;

    double T = 0.0000159;//длительность сигнала
           double F = 62500; //частота сигнала
           double F_d = 6250000;//частота дискретизации

         int  N = data.count();

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);


    for (int i = 0; i< N;i++){
//        qreal val1 = 2 * 3.14 * F * i/F_d;
//        qreal val = qSin(val1);
        in[i][0] = data.at(i);
        in[i][1] = 0;
    }


    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(p); /* repeat as needed */


    for (int i = 0; i< 100;i++){
//        qDebug() <<"[0]"<< out[i][0];
//        qDebug() <<"[1]"<< out[i][1];

//        qDebug() <<"SQRT" <<sqrt( out[i][0]*out[i][0] + out[i][1]*out[i][1] );
    }
    int index = 0;
    double max = sqrt( out[0][0]*out[0][0] + out[0][1]*out[0][1] );
    for ( int i = 1; i< N;i++){
        double new_val = sqrt( out[i][0]*out[i][0] + out[i][1]*out[i][1] );

        out_vector.append( new_val );

        if (new_val>max){
            index = i;
            max = new_val;
        }
    }
    qDebug() << "MAX" << max;
    qDebug() << "MAX index" << index;

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    return out_vector;

}
