#include "settings.h"
#include "ui_settings.h"

#include <QDebug>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::setDeviceList(QStringList list)
{
    ui->cbDevices->addItems(list);
}

QString Settings::getMacSource()
{
    QString text = ui->leSrcMac->text().remove(QChar(' '));
    return text.isEmpty() ? "000000000000" : text;
}

QString Settings::getMacDestination()
{
    QString text = ui->leDstMac->text().remove(QChar(' '));
    return text.isEmpty() ? "000000000000" : text;
}

QString Settings::getDeviceDescription()
{
    return ui->cbDevices->currentText();
}

void Settings::setMacSource(QString str)
{
    ui->leSrcMac->setText( str );
}

void Settings::setMacDestination(QString str)
{
    ui->leDstMac->setText( str );
}

void Settings::setDeviceDescription(QString str)
{
    int i = 0;
    for (i = 0; i < ui->cbDevices->count(); ++i) {
        if (str==ui->cbDevices->itemText(i))
            break;
    }
    ui->cbDevices->setCurrentIndex(i);
}
