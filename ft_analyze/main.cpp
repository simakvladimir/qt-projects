#include <QCoreApplication>
#include "host/ocldft.h"

#include <QDebug>
#include <math.h>

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);


    OclDft *obj = new OclDft();
//    return a.exec();

    qDebug() << "Init" << obj->init() << obj->getErrorDescription();

    cl_float2 in[20];
    cl_float2 out[20];

    for (int i=0;i<20; i++){
        in[i].x = sin(2 * M_PI * i * 10/ 40 );
        in[i].y = 0;
    }

    qDebug() << "Calc" << obj->calculate(in,out,20,1);

    for (int i=0;i<20; i++){
        qDebug() << in[i].x << " | " << out[i].x << "" << out[i].y;
    }

    return 0;
}
