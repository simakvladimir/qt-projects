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

qlonglong Settings::getMacSource()
{
    bool isOK;
    qulonglong value = ui->leSrcMac->text().remove(QChar(' ')).toULongLong(&isOK,16);
    return ui->leSrcMac->text().isEmpty() ? 0 : value;
}

qlonglong Settings::getMacDestination()
{
    bool isOK;
    qulonglong value = ui->leDstMac->text().remove(QChar(' ')).toULongLong(&isOK,16);
    return ui->leSrcMac->text().isEmpty() ? 0 : value;
}

QString Settings::getDeviceDescription()
{
    return ui->cbDevices->currentText();
}

void Settings::setMacSource(qulonglong value)
{
    ui->leSrcMac->setText( uintToHexStr(value, 6) );
}

void Settings::setMacDestination(qulonglong value)
{
    ui->leDstMac->setText( uintToHexStr(value, 6) );
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
