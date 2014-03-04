#include "macwrap.h"
#include <QDebug>

MacWrap::MacWrap(QObject *parent) :
    QObject(parent),
    _fp(NULL),
    rxThr(NULL)
{
    scanDevice();
}

void MacWrap::scanDevice()
{
    QString description;
    pcap_if_t *alldevs;
    pcap_if_t *d;
    int i=0;
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* auth is not needed */, &alldevs, errbuf) == -1)
    {
        devicesHash.clear();
    }

    for(d= alldevs; d != NULL; d= d->next)
    {
        qDebug("%d. %s", ++i, d->name);

        description = d->description ? QString::fromLatin1( d->description ) : "No description available";

        if (d->description)
            qDebug(" (%s)\n", d->description);
        else
            qDebug(" (No description available)\n");

        devicesHash.insert( description,  QString::fromLatin1(d->name) );
    }

    if (i == 0)
    {
        qDebug("\nNo interfaces found! Make sure WinPcap is installed.\n");
        devicesHash.clear();
        return;
    }

    /* We don't need any more the device list. Free it */
    pcap_freealldevs(alldevs);
}

void MacWrap::deviceInitialize(QString name)
{
    _fp = NULL;

    if (rxThr){
        rxThr->stop();
        rxThr->wait();
    }

    pcap_t *fp;
    char errbuf[PCAP_ERRBUF_SIZE];

    if ( (fp = pcap_open( name.toLatin1(),            // name of the device
                        65536,                // portion of the packet to capture (only the first 100 bytes)
                        PCAP_OPENFLAG_PROMISCUOUS,  // promiscuous mode
                        1000,               // read timeout
                        NULL,               // authentication on the remote machine
                        errbuf              // error buffer
                        ) ) == NULL)
    {
        qDebug("\nUnable to open the adapter. %s is not supported by WinPcap\n", "Realtek PCIe GBE Family Controller");
        return;
    }

    _fp = fp;
    qDebug() << "[MAC] OK" << name;
    rxThr = new PortCapturer( fp );
    connect( rxThr, SIGNAL(emit_new_data_available(QByteArray)), this, SLOT(slot_data_available(QByteArray)) );
    rxThr->setFilterMac(_mac_src);
    rxThr->start();
}

void MacWrap::sendPacket(QByteArray data)
{
    if (!_fp)
    {
        qDebug() << "[MacWrap]" << "Not valid ethernet descpitor, maybe not opened";
        return;
    }

    /* Send down the packet */
    if (pcap_sendpacket(_fp, reinterpret_cast<const u_char*>(data.constData()), data.size() /* size */) != 0)
    {
        qDebug("\nError sending the packet: \n", pcap_geterr(_fp));
        return;
    }
}

QStringList MacWrap::getDevicesDesc()
{
    return devicesHash.keys();;
}

void MacWrap::slot_get_settings(qlonglong mac_src, qlonglong mac_dst, QString mac_desc)
{
    _mac_src = mac_src;
    _mac_dst = mac_dst;
    _mac_desc = mac_desc;

    deviceInitialize( devicesHash[_mac_desc] );
}

void MacWrap::slot_data_available(QByteArray data)
{
    emit emit_data_available( data );
}

void MacWrap::slot_get_data_to_send(QByteArray data)
{
    qDebug() << "[MacWrap] Data to send " << data.toHex();
    sendPacket( data );
}

/************************************************************************
 *                              Port Capture
 ************************************************************************/


PortCapturer::PortCapturer(pcap_t *device)
{
    _device = device;
    _stop   = false;
}

PortCapturer::~PortCapturer()
{
    _stop = false;
    wait();
}

void PortCapturer::run()
{
    int ret;
    bool isOk;
    struct pcap_pkthdr *header;
    const u_char       *pkt_data;

    QByteArray data;

    while(!_stop){

        ret = pcap_next_ex(_device, &header, &pkt_data);
        switch (ret){
            case 0:
                // timeout: just go back to the loop
                break;
            case 1:
                data.clear();
                for(uint i=0;i<header->len;i++)
                    data.append(pkt_data[i]);

                if (data.mid(0,6).toHex().toLongLong(&isOk,16) != _mac)
                    continue;

                emit emit_new_data_available( data );
                break;
            default:
                break;
        }

    }
    qDebug() << "[PortCapture] thread is ended";
}

void PortCapturer::stop()
{
    _stop = true;
}
