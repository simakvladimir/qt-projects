#include "comport.h"

#include <QDebug>

void ComPort::OpenComPort( bool result  )
{
    qDebug() << this->thread();
    result = this->open(QIODevice::ReadWrite);


}

void ComPort::SendDataComPort( const QByteArray &data_to_port )
{
//    while(true)  //Check that it's real thread
//    {
//        qDebug() << "LOOP";
//    }
    qint64 size = this->write( data_to_port );
     qDebug() << this->thread();
     qDebug() << "Send " << size << " bytes";
     //    refreshView();
}

void ComPort::ReceivedData()
{

}
