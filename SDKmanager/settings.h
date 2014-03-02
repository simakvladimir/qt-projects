#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QHash>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void setDeviceList(QStringList list);

    QString getMacSource();
    QString getMacDestination();
    QString getDeviceDescription();

    void setMacSource( QString str );
    void setMacDestination( QString str );
    void setDeviceDescription( QString str );

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
