#ifndef WIRINGPRESENTER_H
#define WIRINGPRESENTER_H

#include <QObject>
#include "diodemodel.h"
#include "portaudiowrapper.h"
#include "fftwcompute.h"
#include "fftw_thread.h"

#include <QRgb>
#include <QHash>

class IDiodeView;

class DiodePresenter : public QObject
{
    Q_OBJECT

public:
    explicit DiodePresenter(IDiodeView *view, QObject *parent = 0);

private:
    void refreshView() const;

    PortAudioWrapper    *port_audio;
    FFTW_Thread         *fftw_thr;
    DiodeModel          *m_model;
    IDiodeView          *m_view;
    QHash<QString, int>  sound_devices;
    SafeBuffer           fifo_buf;

signals:
    void emitOpenComSignal(bool error);
    void emitSendComSignal(const QByteArray &array);



private slots:
    void startSetConnection();
    void openComPort();
    void closeComPort();
    void ColorChanged( QRgb rgb );
    void SetCaptureSound(bool on_off , QString device_name);
    void SendColorOnBoard( MyArray data );

};

#endif // WIRINGPRESENTER_H
