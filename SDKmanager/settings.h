#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QHash>

namespace Ui {
class Settings;
}

#define uintToHexStr(num, bytes)    \
    QString("%1").arg(num, bytes*2, 16, QChar('0'))

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void setDeviceList(QStringList list);

    qlonglong getMacSource();
    qlonglong getMacDestination();
    QString getDeviceDescription();

    void setMacSource(qulonglong value );
    void setMacDestination(qulonglong value );
    void setDeviceDescription( QString str );

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
