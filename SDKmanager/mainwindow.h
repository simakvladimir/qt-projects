#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include "settings.h"

/* Protocol Headers */
#include "rxpacket.h"
#include "txpacket.h"

namespace Ui {
class MainWindow;
}

;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSize winSize;

    struct {
        qlonglong mac_src;
        qlonglong mac_dst;
        QString eth_desc;
    } appSettings;
    Settings *settingForm;

    RxPacket _rx_data;

    QQuickView *view;
    QObject    *_qml_main;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDeviceList(QStringList );

    void updateGuiState();

    Q_INVOKABLE RxPacket *getRxPcktPonter(){ return &_rx_data; };

private slots:

    void on_actnTuneMAC_triggered();
    void on_actnShowTable_triggered();
    void on_buttonRedLedClicked(bool state);
    void on_buttonGreenLedClicked(bool state);
    void on_buttonYellowLedClicked(bool state);
    void on_buttonTelemetryClicked(bool state);

    void get_settings_from_dialog();

    void get_new_data_available(QByteArray data);

private:
    Ui::MainWindow *ui;

signals:
    void signal_mac_settings( qlonglong, qlonglong, QString );

    /* QML */
    void signalUpdateQMLState();

    /*  */
    void signal_data_to_send(QByteArray);
};

#endif // MAINWINDOW_H
