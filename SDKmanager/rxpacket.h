#ifndef RXPACKET_H
#define RXPACKET_H

#include <QtCore>

class RxPacket : public QObject
{
    Q_OBJECT
private:
    struct{
        char mac_dst[6];
        char mac_src[6];
        quint16 pkt_length;
        quint8 rled_state;
        quint8 gled_state;
        quint8 yled_state;
        quint8 jmp_modem_state;
        quint8 jmp_rs_state;
        quint8 jmp_lock_state;
        quint8 jmp_mif_state;
        quint8 jmp_prog_state;
        quint8 jmp_ext1_state;
        quint8 jmp_ext2_state;
        quint8 telem_state;
        quint32 sdk_time;
    }_rx_pkt;

public:
    explicit RxPacket(QObject *parent = 0 ) {}

    void setData( QByteArray array ){ mempcpy(&_rx_pkt, array.data(), sizeof(_rx_pkt)); };

    QString getMacDst(){ return QString::fromLatin1(_rx_pkt.mac_dst); }
    QString getMacSrc(){ return QString::fromLatin1(_rx_pkt.mac_src); }
    unsigned getPckLength(){return _rx_pkt.pkt_length;}
    Q_INVOKABLE bool isRedLedOn()   { return _rx_pkt.rled_state ? true : false; }
    Q_INVOKABLE bool isGreenLedOn() { return _rx_pkt.gled_state ? true : false; }
    Q_INVOKABLE bool isYellowLedOn(){ return _rx_pkt.yled_state ? true : false; }
signals:

public slots:

};

#endif // RXPACKET_H
