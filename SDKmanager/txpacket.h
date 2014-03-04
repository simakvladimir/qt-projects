#ifndef TXPACKET_H
#define TXPACKET_H

#include <QObject>

class TxPacket : public QObject
{
    Q_OBJECT
private:
    struct{
        char mac_dst[6];
        char mac_src[6];
        quint16 pkt_length;
        quint16 op_code;
        quint32 param;
        quint32 timePC;
    }_tx_pkt;

public:
    enum cmd_type{
        CMD_RED_LED,
        CMD_GREEN_LED,
        CMD_YELLOW_LED,
        CMD_TELEMETRY
    };
    enum cmd_param{
        OFF,
        ON
    };

    explicit TxPacket(QObject *parent = 0);

    void setMacDst( qlonglong mac ){  for(int i=0; i<6;i++)
                                         _tx_pkt.mac_dst[i] = mac & (0xFF0000000000 >> i*8) ;
                                   }
    void setMacSrc( qlonglong mac ){  for(int i=0; i<6;i++)
                                        _tx_pkt.mac_src[i] = mac & (0xFF0000000000 >> i*8) ;
                                   }
    void setPktLength( unsigned short length ) { _tx_pkt.pkt_length = length; }
    void setPktLength(){_tx_pkt.pkt_length = sizeof(_tx_pkt) - 6 - 6 - 2; };
    void setCmdCode( cmd_type code ){ _tx_pkt.op_code = code; }
    void setCmdParam( cmd_param param ){ _tx_pkt.param = param; }
    void setCmdParam( int time ){ _tx_pkt.timePC = time; }

signals:

public slots:

};

#endif // TXPACKET_H
