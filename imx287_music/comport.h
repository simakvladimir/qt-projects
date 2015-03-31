#ifndef COMPORT_H
#define COMPORT_H

#include <QObject>
#include "qextserialport.h"

class ComPort: public QextSerialPort
{
      Q_OBJECT
public:
    ComPort( const QString &name, QextSerialPort::QueryMode mode ):QextSerialPort( name, mode ){};

signals:


public slots:
    void OpenComPort( bool result );
    void SendDataComPort( const QByteArray &data_to_port );
    void ReceivedData();

};

#endif // COMPORT_H
