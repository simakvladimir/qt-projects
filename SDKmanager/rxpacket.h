#ifndef RXPACKET_H
#define RXPACKET_H

#include <QtCore>
#include <QTime>

class RxPacket : public QObject
{
    Q_OBJECT
private:
    struct{
        char mac_dst[6];
        char mac_src[6];
        char pkt_length[2];
        char rled_state;
        char gled_state;
        char yled_state;
        char jmp_modem_state;
        char jmp_rs_state;
        char jmp_lock_state;
        char jmp_mif_state;
        char jmp_prog_state;
        char jmp_ext1_state;
        char jmp_ext2_state;
        char telem_state;
        char sdk_time[4];
    }_rx_pkt;

public:
    explicit RxPacket(QObject *parent = 0 ) {}

    void setData( QByteArray array ){ mempcpy(&_rx_pkt, array.data(), sizeof(_rx_pkt)); };

    QString getMacDst(){ return QString::fromLatin1(_rx_pkt.mac_dst); }
    QString getMacSrc(){ return QString::fromLatin1(_rx_pkt.mac_src); }
    unsigned getPckLength(){return (_rx_pkt.pkt_length[1] | (_rx_pkt.pkt_length[0] << 8)) & 0xFFFF;}

    Q_INVOKABLE bool isRedLedOn()   { return _rx_pkt.rled_state ? true : false; }
    Q_INVOKABLE bool isGreenLedOn() { return _rx_pkt.gled_state ? true : false; }
    Q_INVOKABLE bool isYellowLedOn(){ return _rx_pkt.yled_state ? true : false; }


    Q_INVOKABLE QString getSDKTime(){
        int time;
        time = (_rx_pkt.sdk_time[0] << 8*3) | (_rx_pkt.sdk_time[1] << 8*2) | (_rx_pkt.sdk_time[2] << 8*1) | (_rx_pkt.sdk_time[3]);

        qDebug() << "Time" << time;
        QTime qtime(0,0);
        return  qtime.addMSecs(time).toString("hh:mm:ss.zzz");
    }
signals:

public slots:

};

#endif // RXPACKET_H
