#include "macwrap.h"
#include <QDebug>

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
//    struct tm ltime;
//    char timestr[16];
//    time_t local_tv_sec;

//    /*
//     * unused variables
//     */
//    (VOID)(param);
//    (VOID)(pkt_data);

//    /* convert the timestamp to readable format */
//    local_tv_sec = header->ts.tv_sec;
//    localtime_s(&ltime, &local_tv_sec);
//    strftime( timestr, sizeof timestr, "%H:%M:%S", &ltime);

//    printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);
}

MacWrap::MacWrap(QObject *parent) :
    QObject(parent),
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

    qDebug() << "[MAC] OK" << name;
    rxThr = new PortCapturer( fp );
    connect( rxThr, SIGNAL(emit_new_data_available(QString)), this, SLOT(slot_data_available(QString)) );
    rxThr->start();
}

QStringList MacWrap::getDevicesDesc()
{
    return devicesHash.keys();;
}

void MacWrap::slot_get_settings(QString mac_src, QString mac_dst, QString mac_desc)
{
    _mac_src = mac_src;
    _mac_dst = mac_dst;
    _mac_desc = mac_desc;

    deviceInitialize( devicesHash[_mac_desc] );
}

void MacWrap::slot_data_available(QString data)
{
    emit emit_data_available( data );
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
    struct pcap_pkthdr *header;
    const u_char       *pkt_data;

    QString data;

    while(!_stop){

        ret = pcap_next_ex(_device, &header, &pkt_data);
        switch (ret){
            case 0:
                // timeout: just go back to the loop
                break;
            case 1:
                data.clear();
                for(uint i=0;i<header->len;i++){
                    data.append( QString::number( (int)pkt_data[i], 16 ) );
                }
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
