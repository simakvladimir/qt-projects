#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QQuickView>
#include <QQmlContext>
#include "settings.h"

/* Protocol Headers */
#include "rxpacket.h"

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
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDeviceList(QStringList );

    void updateGuiState();

    Q_INVOKABLE RxPacket *getRxPcktPonter(){ return &_rx_data; };

private slots:

    void on_actnTuneMAC_triggered();

    void on_actnShowTable_triggered();

    void get_settings_from_dialog();

    void get_new_data_available(QByteArray data);

private:
    Ui::MainWindow *ui;

signals:
    void signal_mac_settings( qlonglong, qlonglong, QString );

    /* QML */
    void signalRedLedState();
};

#endif // MAINWINDOW_H
