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
    QObject::connect( settingForm, SIGNAL(accepted()), this, SLOT(get_settings_from_dialog()) );

    /* QML interface */
    QObject::connect(view->rootObject(), SIGNAL(buttonRedLedClicked(bool)),
                                   this, SLOT(on_buttonRedLedClicked(bool)));
    QObject::connect(view->rootObject(), SIGNAL(buttonGreenLedClicked(bool)),
                                   this, SLOT(on_buttonGreenLedClicked(bool)));
    QObject::connect(view->rootObject(), SIGNAL(buttonYellowLedClicked(bool)),
                                   this, SLOT(on_buttonYellowLedClicked(bool)));
    QObject::connect(view->rootObject(), SIGNAL(buttonTelemetryClicked(bool)),
                                   this, SLOT(on_buttonTelemetryClicked(bool)));

    // on first run, table is hiden
    ui->tblRxPct->setVisible(false);


    QQmlEngine engine;
    QQmlComponent component(&engine, "main.qml");
    _qml_main = component.create();
}

void MainWindow::setDeviceList(QStringList list)
{
    settingForm->setDeviceList(list);
}

void MainWindow::updateGuiState()
{
    emit signalUpdateQMLState();

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

/**
 * QML Button on Led is clcked
 */
void MainWindow::on_buttonRedLedClicked(bool state)
{
    qDebug() << "[QML] Red Button"<< state;
    TxPacket tx_pckt;
    tx_pckt.createFullPacket(appSettings.mac_dst,
                             appSettings.mac_src,
                             TxPacket::CMD_RED_LED,
                             state ? TxPacket::ON : TxPacket::OFF,
                             QTime::currentTime());

    emit signal_data_to_send(tx_pckt.getData());
}

void MainWindow::on_buttonGreenLedClicked(bool state)
{
    qDebug() << "[QML] Green Button"<< state;
    TxPacket tx_pckt;
    tx_pckt.createFullPacket(appSettings.mac_dst,
                             appSettings.mac_src,
                             TxPacket::CMD_GREEN_LED,
                             state ? TxPacket::ON : TxPacket::OFF,
                             QTime::currentTime());

    emit signal_data_to_send(tx_pckt.getData());
}

void MainWindow::on_buttonYellowLedClicked(bool state)
{
    qDebug() << "[QML] Yellow Button"<< state;
    TxPacket tx_pckt;
    tx_pckt.createFullPacket(appSettings.mac_dst,
                             appSettings.mac_src,
                             TxPacket::CMD_YELLOW_LED,
                             state ? TxPacket::ON : TxPacket::OFF,
                             QTime::currentTime());

    emit signal_data_to_send(tx_pckt.getData());
}

void MainWindow::on_buttonTelemetryClicked(bool state)
{
    qDebug() << "[QML] Telemetry Button"<< state;
    TxPacket tx_pckt;
    tx_pckt.createFullPacket(appSettings.mac_dst,
                             appSettings.mac_src,
                             TxPacket::CMD_TELEMETRY,
                             state ? TxPacket::ON : TxPacket::OFF,
                             QTime::currentTime());

    emit signal_data_to_send(tx_pckt.getData());
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
    qDebug() << "[MW]" << "NEW data";
    _rx_data.setData(data);
    _rx_data.getSDKTime();

//    for (int i=0;i<6;i++){
//        qDebug() << "[RX pck] dst[" <<i<<"]" << _rx_data.getMacDst().at(i).unicode();
//    }
//    for (int i=0;i<6;i++){
//        qDebug() << "[RX pck] src[" <<i<<"]" << QString("%1").arg( _rx_data.getMacSrc().toLatin1().at(i), 0, 16, QChar('0'));
//    }

    qDebug() << "[RX pck] pck length" << _rx_data.getPckLength();
    qDebug() << "[RX pck] R LED" << _rx_data.isRedLedOn();
    qDebug() << "[RX pck] Y LED" << _rx_data.isYellowLedOn();
    qDebug() << "[RX pck] G LED" << _rx_data.isGreenLedOn();

    updateGuiState();
}
