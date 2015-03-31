#ifndef WIRINGMODEL_H
#define WIRINGMODEL_H

#include <QObject>
#include "comport.h"

#define COM_MIN_SPEED 9600

#define COMMAND_BIT     0x80
#define TICKET_BIT      0x40
#define PARAMETER_BIT   0x20
#define COMMAND_CODE    0x1F
#define PARAMETERS      4

class DiodeModel: public QObject
{
    Q_OBJECT
public:
    enum com_return {
        OPEN_SUCCESS = 0,
        OPEN_FAILED
    };
    enum com_type {
        SET_SPEED = 0,
        COLOR
    };

public:
    explicit DiodeModel( QObject *parent = 0 );

    void CreateComPort( QString PortName );
    void CloseComPort( void );
    void ConfigureComPort( BaudRateType baudRate );
    QByteArray CreateCommand(com_type command, QByteArray &param );


    com_return error;

private:
    QObject *qparent;

signals:
    void OpenEmit();

public slots:
    void onReadyRead();
//    void WriteDataOnCom(const QByteArray &data_to_port );
//    void OpenComPort();

public:
   ComPort *port;
};

#endif // WIRINGMODEL_H
