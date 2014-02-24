#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QMutex>
#include <QTime>
#include "bustthread.h"
#include "BigIntLib/BigIntegerLibrary.hh"

class ThrWrap : public QObject
{
    Q_OBJECT
private:
    unsigned thread_number;
    unsigned digit;
    quint64 bottom;
    quint64 top;
    quint64 counter;
    unsigned    finish_counter;
    QMutex      mtx;
    QTime       start_time;
    QTime       finish_time;
public:
    explicit ThrWrap(QObject *parent = 0);

    Q_INVOKABLE QString get_start_time(){ return start_time.toString(); }
    Q_INVOKABLE QString get_finish_time(){ return finish_time.toString(); }
    Q_INVOKABLE QString get_duration_time(){ return  /*QString::number(start_time.msecsTo(finish_time));*/QTime(0,0).addMSecs(start_time.msecsTo(finish_time) ).toString("hh:mm:ss.zzz"); }
    Q_INVOKABLE unsigned get_thread_number(){ return thread_number; }

    Q_INVOKABLE unsigned get_cpu_numbers();
    Q_INVOKABLE QString get_cpu_brand();
    Q_INVOKABLE void set_thread_number( unsigned value ){ thread_number = value; }
    Q_INVOKABLE void set_digit( unsigned value ) { digit = value; }
    Q_INVOKABLE void set_range( quint64 low, quint64 high ){ bottom = low; top = high; }
    Q_INVOKABLE void calculate();
    Q_INVOKABLE void create_range_by_digit(unsigned digit);
    Q_INVOKABLE QString get_counter(){ return QString::number( counter ); }

signals:
    void calculateFinish();
public slots:
    void created_thr_finish(quint64 value);

};

#endif // PROCESS_H
