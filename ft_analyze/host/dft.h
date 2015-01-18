#ifndef DFT_H
#define DFT_H

#include "ifouriertransform.h"
#include <math.h>

#include <QObject>
#include <QSettings>

class Dft : public QObject, public IFourierTransform
{
    Q_OBJECT
public:
    explicit Dft(QObject *parent = 0);
    ~Dft(){};

    bool calculate(const cl_float2 *in, // complex values input (packed real and imaginary)
        cl_float2 *out,      // complex values output
        int length,       // number of input and output values
        int sign
    );

    bool init();
    bool getDeviceInfo();

    QString getErrorDescription() { return error; }

signals:

public slots:

private:
    QString error;
};

#endif // DFT_H
