#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "macwrap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MacWrap mac;
    MainWindow w;

    QObject::connect( &w,   SIGNAL(signal_mac_settings(qlonglong,qlonglong,QString)),
                    &mac, SLOT(slot_get_settings(qlonglong,qlonglong,QString)));

    QObject::connect( &w,   SIGNAL(signal_data_to_send(QByteArray)),
                    &mac, SLOT(slot_get_data_to_send(QByteArray)));
    QObject::connect( &mac,   SIGNAL(emit_data_available(QByteArray)),
                        &w, SLOT(get_new_data_available(QByteArray)));

    w.setDeviceList( mac.getDevicesDesc() );
    w.show();

    return a.exec();
}
