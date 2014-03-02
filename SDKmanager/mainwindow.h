#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include "settings.h"

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
        QString mac_src;
        QString mac_dst;
        QString eth_desc;
    } appSettings;
    Settings *settingForm;

public:
    explicit MainWindow(QWidget *parent = 0);

    void setDeviceList(QStringList );

    ~MainWindow();

private slots:

    void on_actnTuneMAC_triggered();

    void on_actnShowTable_triggered();

    void get_settings_from_dialog();

    void get_new_data_available(QString data);

private:
    Ui::MainWindow *ui;

signals:
    void signal_mac_settings( QString, QString, QString );
};

#endif // MAINWINDOW_H
