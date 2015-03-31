#include "safebuffer.h"
#include <QDebug>

SafeBuffer::SafeBuffer()
{
}

void SafeBuffer::push( float value ){
    fifo.append( value );
}

float SafeBuffer::pop( bool *isEmpty ){
    float ret;
    if (fifo.isEmpty()){
        *isEmpty = true;
    } else {
       *isEmpty = false;
        ret = fifo.first();
//        qDebug() <<"Fifo"<< fifo.count();
        fifo.remove( 0 );
    }
    return ret;
}

void SafeBuffer::lock()
{
    mtx.lock();
}

void SafeBuffer::unlock()
{
    mtx.unlock();
}

void SafeBuffer::clear()
{
    fifo.clear();
}

bool SafeBuffer::is_empty()
{
    return fifo.isEmpty();
}

