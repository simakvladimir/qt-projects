#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    winSize(400,600),
    settingForm(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    appSettings.mac_dst = appSettings.mac_src = 0;
//    connect(ui->pushButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setMinimumSize(winSize);
    container->setMaximumSize(winSize);
    container->setFocusPolicy(Qt::TabFocus);
    view->rootContext()->setContextProperty("MainWin", this);
    view->rootContext()->setContextProperty("RxData", &_rx_data);
    view->setSource(QUrl("qml/main.qml"));
    ui->verticalLayout->addWidget(container);

    winSize = size();

    settingForm = new Settings;
    connect( settingForm, SIGNAL(accepted()), this, SLOT(get_settings_from_dialog()) );

    // on first run, table is hiden
    ui->tblRxPct->setVisible(false);
}

void MainWindow::setDeviceList(QStringList list)
{
    settingForm->setDeviceList(list);
}

void MainWindow::updateGuiState()
{
    emit signalRedLedState();

    /* table */
//    ui->tblRxPct->
}

MainWindow::~MainWindow()
{
    delete view;
    delete ui;
}

/**********************************************************************
 *                              SLOTS
 *********************************************************************/
void MainWindow::on_actnTuneMAC_triggered()
{
    settingForm->setMacSource( appSettings.mac_src );
    settingForm->setMacDestination( appSettings.mac_dst );
    settingForm->setDeviceDescription( appSettings.eth_desc  );

    settingForm->show();
}

void MainWindow::on_actnShowTable_triggered()
{
    bool isShowed = ui->actnShowTable->isChecked();
    ui->tblRxPct->setVisible(isShowed);
}

void MainWindow::get_settings_from_dialog()
{
    appSettings.mac_src = settingForm->getMacSource();
    appSettings.mac_dst = settingForm->getMacDestination();
    appSettings.eth_desc = settingForm->getDeviceDescription();

    emit signal_mac_settings( appSettings.mac_src,
                              appSettings.mac_dst,
                              appSettings.eth_desc );
}

void MainWindow::get_new_data_available(QByteArray data)
{
    qDebug() << "[MW]" << data;
    _rx_data.setData(data);
    updateGuiState();
}
