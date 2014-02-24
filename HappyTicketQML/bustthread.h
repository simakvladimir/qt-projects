#ifndef BUSTTHREAD_H
#define BUSTTHREAD_H

#include <QThread>
//#include "BigIntLib/BigIntegerLibrary.hh"

class BustThread : public QThread
{
    Q_OBJECT
private:
    quint64 digit;
    quint64 bottom;
    quint64 top;
    quint64 counter;
public:
    explicit BustThread(QObject *parent = 0);

    void SetRange( quint64 low, quint64 high ){
        bottom = low;
        top    = high;
    }

    void SetDigit( quint64 value ){ digit = value; }
    quint64 get_counter(){ return counter; }

protected:
    void run();

signals:
    void thr_finish(quint64);

public slots:

};

#endif // BUSTTHREAD_H
