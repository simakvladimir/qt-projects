#ifndef MACWRAP_H
#define MACWRAP_H

#include <QObject>
#include <QThread>
#include <QHash>
#include <QMutex>

#include "rxpacket.h"

#define HAVE_REMOTE
#include <pcap.h>

class PortCapturer: public QThread
{
    Q_OBJECT
public:
    PortCapturer(pcap_t *device);
    ~PortCapturer();
    void run();
    void stop();
    void setFilterMac(qlonglong mac){_mac=mac;}
protected:
    void	timerEvent(QTimerEvent * e);

private:
    pcap_t         *_device;
    volatile bool   _stop;
    qlonglong       _mac;
    QMutex          _mtx;
    QTime           _time;
signals:
    void emit_new_data_available( QByteArray data );
    void emit_timeout( int time );
};

/*****************************************************************
 *
 *****************************************************************/
class MacWrap : public QObject
{
    Q_OBJECT
private:
    QHash<QString, QString> devicesHash;

    qlonglong _mac_src;
    qlonglong _mac_dst;
    QString _mac_desc;

    pcap_t  *_fp;

    PortCapturer *rxThr;
public:
    explicit MacWrap(QObject *parent = 0);

    void scanDevice();
    void deviceInitialize( QString name );

    void sendPacket( QByteArray data );

    QStringList getDevicesDesc();
signals:
    void emit_data_available(QByteArray);
    void emit_data_timeout(int);
public slots:
    void slot_get_settings(qlonglong mac_src,
                            qlonglong mac_dst,
                            QString mac_desc );
    void slot_data_available(QByteArray data);
    void slot_get_data_to_send(QByteArray data);
    void slot_get_timeout(int time);

};

#endif // MACWRAP_H
