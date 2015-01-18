#ifndef QFUNC3D_H
#define QFUNC3D_H

#include <qwt3d_function.h>

class QFunc3D : public Qwt3D::Function
{
public:
    QFunc3D(Qwt3D::SurfacePlot *,
        double *,double *,double *,
        int,int);
    ~QFunc3D();

    double operator()(double,double);
    void setScale(double value) { scale = value; }
private:
    double *xd,*yd,*zd;
    int Nx,My;
    double scale;
};

#endif // QFUNC3D_H
