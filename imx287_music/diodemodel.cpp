#include <QDebug>
#include "diodemodel.h"
#include <QThread>
#include <QDebug>

DiodeModel::DiodeModel(QObject *parent): qparent(parent)

{
}


void DiodeModel::CreateComPort( QString PortName )
{
    QThread* thread = new QThread;

    qDebug() << this->thread();

//  this->moveToThread(thread);

    port = new ComPort( PortName,
                             QextSerialPort::Polling
                           );
//    this->parent()
    port->moveToThread(thread);
    qDebug() << this->thread();
    qDebug() << port->thread();
    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    QObject::connect(qparent, SIGNAL(emitOpenComSignal(bool)), port, SLOT(OpenComPort(bool)));
    QObject::connect(qparent, SIGNAL(emitSendComSignal(const QByteArray)), port, SLOT(SendDataComPort(const QByteArray)));
    //    connect(thread, SIGNAL(started(const QByteArray)), this, SLOT( WriteDataOnCom(const QByteArray )));
    thread->start();
}




/* TODO need add parameters, return value */
void DiodeModel::ConfigureComPort( BaudRateType baudRate )
{
    port->setBaudRate( baudRate );
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_2);
    qDebug() << port->thread();
}

void DiodeModel::CloseComPort()
{
    port->close();
}

QByteArray DiodeModel::CreateCommand( com_type command, QByteArray &param )
{
    QByteArray    full_command;
    unsigned char code_command;
    unsigned int speed = 0;

    code_command    = COMMAND_CODE & (unsigned char)command;
    full_command[0] = COMMAND_BIT & ( ~TICKET_BIT );

    switch ( command ){

        case SET_SPEED:
                    //full_command[0] = full_command[0] | code_command & (~PARAMETER_BIT);
                    full_command[0] = full_command[0]| PARAMETER_BIT | code_command;
                    full_command.insert(1,param);
                    full_command.resize(5);

                    speed |=  (param.at(1) << 16) | 1;
                    qDebug() << speed;
                    ConfigureComPort(BaudRateType(speed));

                    break;

        case COLOR: full_command[0] = full_command[0]| PARAMETER_BIT | code_command;
                    full_command.insert(1,param);
                    full_command.resize(5) ;break;

        default: break;
    }

    int a;
    a++;
    return full_command;

}


void DiodeModel::onReadyRead(  )
{
    QByteArray bytes;
    int a = port->bytesAvailable();
    bytes.resize(a);
    port->read(bytes.data(), bytes.size());
    qDebug() << "bytes read:" << bytes.size();
    qDebug() << "bytes:" << bytes;


}
