#ifndef SAFEBUFFER_H
#define SAFEBUFFER_H

#include <QVector>
#include <QMutex>


class SafeBuffer
{
public:
    SafeBuffer();
    void  push( float value );
    float pop( bool *isEmpty );

    void lock();
    void unlock();

    void clear();
    bool is_empty();
private:
    QVector<float> fifo;
    QMutex          mtx;

};

#endif // SAFEBUFFER_H
