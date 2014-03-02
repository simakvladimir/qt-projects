#ifndef MACWRAP_H
#define MACWRAP_H

#include <QObject>
#include <QThread>
#include <QHash>

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
    void emit_new_data_available( QString data );
};

/*****************************************************************
 *
 *****************************************************************/
class MacWrap : public QObject
{
    Q_OBJECT
private:
    QHash<QString, QString> devicesHash;

    QString _mac_src;
    QString _mac_dst;
    QString _mac_desc;

    PortCapturer *rxThr;
public:
    explicit MacWrap(QObject *parent = 0);

    void scanDevice();
    void deviceInitialize( QString name );

    QStringList getDevicesDesc();
signals:
    void emit_data_available(QString);
public slots:
    void slot_get_settings( QString mac_src,
                            QString mac_dst,
                            QString mac_desc );
    void slot_data_available(QString data);

};

#endif // MACWRAP_H
