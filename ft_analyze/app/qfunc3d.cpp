#include "qfunc3d.h"

#include <QDebug>

QFunc3D::QFunc3D(Qwt3D::SurfacePlot *sp,
        double *x,double *y,double *z,
        int N,int M) :
    Function(sp),
    scale(1.0)
{
    xd = (double *)malloc((N)*sizeof(double));
    yd = (double *)malloc((M)*sizeof(double));
    zd = (double *)malloc((N*M)*sizeof(double));
    for (int k=0; k < N; k++)
        xd[k] = x[k];
    for (int q=0; q < M; q++)
    {
        yd[q] = y[q];
        for (int k=0; k < N; k++)
            zd[q*N+k] = z[q*N+k];
    }
    Nx = N; My = M;
}

QFunc3D::~QFunc3D()
{
    free((void *)xd);
    free((void *)yd);
    free((void *)zd);
}

double QFunc3D::operator()(double x,double y)
{
    double dx = (xd[Nx-1]-xd[0]) / (Nx-1);
    int n = floor((x-xd[0])/dx + 0.5);
    if (n < 0 || n > Nx-1) return 0;
    double dy = (yd[My-1]-yd[0]) / (My-1);
    int m = floor((y-yd[0])/dy + 0.5);
    if (m < 0 || m > My-1) return 0;
//    qDebug() << zd[m*Nx+n] << m*Nx+n;
    return zd[m*Nx+n] * scale;
}
