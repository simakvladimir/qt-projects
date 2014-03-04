#ifndef TXPACKET_H
#define TXPACKET_H

#include <QObject>
#include <QTime>
#include <QDebug>

class TxPacket : public QObject
{
    Q_OBJECT
private:
    struct{
        char mac_dst[6];
        char mac_src[6];
        char pkt_length[2];
        char op_code[2];
        char param[4];
        char timePC[9];
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

    explicit TxPacket(QObject *parent = 0){};

    void setMacDst( qlonglong mac ){  for(int i=0; i<6;i++)
                                         _tx_pkt.mac_dst[i] = (mac >> (6-i-1)*8)&0xFF;
                                   }
    void setMacSrc( qlonglong mac ){  for(int i=0; i<6;i++)
                                        _tx_pkt.mac_src[i] = (mac >> (6-i-1)*8)&0xFF;
                                   }
    void setPktLength( quint16 length ) { for(int i=0; i<2;i++)
                                            _tx_pkt.pkt_length[i] = (length >> (2-i-1)*8)&0xFF; }
    void setPktLength(){for(int i=0; i<2;i++)
                          _tx_pkt.pkt_length[i] = ((sizeof(_tx_pkt) - 6 - 6 - 2) >> (2-i-1)*8)&0xFF;
                       }
    void setCmdCode( cmd_type code ){for(int i=0; i<2;i++)
                                        _tx_pkt.op_code[i] = (code >> (2-i-1)*8)&0xFF;
                                     }
    void setCmdParam( cmd_param param ){for(int i=0; i<4;i++)
                                          _tx_pkt.param[i] = (param >> (4-i-1)*8)&0xFF;
                                       }
    void setTimeStamp( QTime time ){ for(int i=0; i<9;i++)
                                        _tx_pkt.timePC[i] = time.toString("hhmmsszzz").at(i).toLatin1();
                                   }

    QByteArray getData(){ return QByteArray((char*)&_tx_pkt,sizeof(_tx_pkt)); }

    void createFullPacket( qlonglong mac_dst, qlonglong mac_src, cmd_type code, cmd_param param, QTime time  ){
        setMacDst(mac_dst);
        setMacSrc(mac_src);
        setPktLength();
        setCmdCode(code);
        setCmdParam(param);
        setTimeStamp(time);
    }

signals:

public slots:

};

#endif // TXPACKET_H
