#include "thrwrap.h"
#include <windows.h>
#include <qmath.h>
#include <QDebug>
#include <QSettings>

ThrWrap::ThrWrap(QObject *parent) :
    QObject(parent),
    start_time(0,0),
    finish_time(0,0)
{
}

unsigned ThrWrap::get_cpu_numbers()
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}

QString ThrWrap::get_cpu_brand()
{
    QString brand;
    QSettings cpuInfo("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", QSettings::NativeFormat);
    brand = cpuInfo.value("ProcessorNameString").toString();

    int j=0;
    int i = brand.indexOf( QChar(' '), 0 );

    while (i>0)
    {

        if ((i-j) >=16) {
            brand.insert( i + 1, "\n" );
            j = i;
        }
        i = brand.indexOf(  QChar(' '), i + 1 );

    }
    return brand;
}

void ThrWrap::calculate()
{
    unsigned i;

    if (!thread_number)
        return;

    counter = 0;
    finish_counter = 0;

    quint64 low = bottom;
    quint64 inc = (top - bottom) / thread_number;
    quint64 mod = ((top - bottom) % thread_number);

    qDebug() << QTime::currentTime();

    start_time = QTime::currentTime();

    for(i=0; i<thread_number; i++){

        BustThread *new_thr = new BustThread(this);
        connect( new_thr, SIGNAL(thr_finish(quint64)), this, SLOT(created_thr_finish(quint64)) );

        new_thr->SetRange( low, low + inc + mod );
        new_thr->SetDigit( digit );
        qDebug() << "#" << i <<"low = " << low << "high = " << low + inc + mod;
        new_thr->start();
        low += inc + mod;
        mod = 0;
    }
}

void ThrWrap::create_range_by_digit( unsigned digit )
{
    bottom = 0;

    top = 1;

    for (unsigned power = 0; power < digit; power++) {
        top *= 10; // A BigInteger assignment operator
    }
}

void ThrWrap::created_thr_finish(quint64 value)
{
    counter += value;
    finish_counter++;
    if  (finish_counter>=thread_number){
        qDebug() << counter << QTime::currentTime();
        finish_time = QTime::currentTime();
        emit calculateFinish();
    }
    sender()->deleteLater();
}
