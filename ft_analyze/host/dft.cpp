#include "dft.h"

#include <windows.h>
#include <QDebug>

Dft::Dft(QObject *parent) :
    QObject(parent)
{
}

bool Dft::calculate(const cl_float2 *in, cl_float2 *out, int length, int sign)
{

    for (int i = 0; i < length; i++)
    {
        double totReal = 0, totImag = 0;
        double param = (-2 * sign * i) * M_PI / (double)length;

        for (int k = 0; k < length; k++) {
            double valueReal = in[k].x, valueImag = in[k].y;
            double arg = k * param;
            double c = cos(arg), s = sin(arg);

            totReal += valueReal * c - valueImag * s;
            totImag += valueReal * s + valueImag * c;
        }

        out[i].x = sqrt(totReal*totReal + totImag * totImag);
        out[i].y = 0;
    }
    return true;
}

bool Dft::init()
{
    if (!getDeviceInfo())
        return false;

    return true;
}

bool Dft::getDeviceInfo()
{
    QString temp;
    QSettings cpuInfo("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", QSettings::NativeFormat);

    temp = cpuInfo.value("ProcessorNameString").toString();
    deviceInfo << QString("%1").arg(temp);

    temp = cpuInfo.value("~MHz").toString();
    deviceInfo << QString("%1").arg(temp);

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    deviceInfo <<  QString("%1").arg(QString::number(sysinfo.dwNumberOfProcessors));

    return true;
}
