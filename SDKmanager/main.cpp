#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "macwrap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MacWrap mac;
    MainWindow w;

    QObject::connect( &w,   SIGNAL(signal_mac_settings(QString,QString,QString)),
                    &mac, SLOT(slot_get_settings(QString,QString,QString)));
    QObject::connect( &mac,   SIGNAL(emit_data_available(QString)),
                        &w, SLOT(get_new_data_available(QString)));

    w.setDeviceList( mac.getDevicesDesc() );
    w.show();

    return a.exec();
}
