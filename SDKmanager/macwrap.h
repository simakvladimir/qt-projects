#ifndef MACWRAP_H
#define MACWRAP_H

#include <QObject>
#include <QThread>
#include <QHash>

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
private:
    pcap_t         *_device;
    volatile bool   _stop;
signals:
    void emit_new_data_available( QByteArray data );
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

    PortCapturer *rxThr;
public:
    explicit MacWrap(QObject *parent = 0);

    void scanDevice();
    void deviceInitialize( QString name );

    QStringList getDevicesDesc();
signals:
    void emit_data_available(QByteArray);
public slots:
    void slot_get_settings(qlonglong mac_src,
                            qlonglong mac_dst,
                            QString mac_desc );
    void slot_data_available(QByteArray data);

};

#endif // MACWRAP_H
