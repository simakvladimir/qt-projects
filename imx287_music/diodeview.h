#ifndef DIODEVIEW_H
#define DIODEVIEW_H

#include <QWidget>
#include "idiodeview.h"
#include "gradient.h"

namespace Ui {
    class DiodeView;
}

class DiodeView : public QWidget, public IDiodeView
{
    Q_OBJECT
protected:
//    void paintEvent(QPaintEvent *);

public:
    explicit DiodeView(QWidget *parent = 0);
    ~DiodeView();

    /* get methods */
    QString getCurrentPortName();
    QString getCurrentSpeed();

    void connection_state(bool error);
    void open_com_state(bool error);
    void update_sound_devices(QHash<QString,int> devices);

    Equalizer*  get_eq();
signals:
    void checkConnection();
    void tryOpenCom();
    void tryCloseCom();
    void RGBColorEmit( QRgb rgb );
    void captureSound( bool on_off, QString device_name );

private:
    Ui::DiodeView *ui;
    bool           isOpen;
    Equalizer     *eq;

private slots:
    void on_set_speed_clicked();
    void on_open_com_clicked();

//public slots:
    void color_changed( QRgb color );
    void on_capture_sound_clicked();
};

#endif // WIRINGFORM_H
