#ifndef IDIODEVIEW_H
#define IDIODEVIEW_H

#include "diodemodel.h"
#include "eq/equalizer.h"
#include <QRgb>
#include <QColor>

/*!
    \interface IWiringView

    Интерфейс представления в триаде MVP расчета электропроводки.
*/

class IDiodeView
{
public:

    virtual QString getCurrentPortName() = 0;
    virtual QString getCurrentSpeed()    = 0;

    virtual Equalizer*  get_eq()  = 0;
    virtual void connection_state(bool error)  = 0;
    virtual void open_com_state(bool error) = 0;
    virtual void update_sound_devices(QHash<QString,int> devices) = 0;

public: // signals
    virtual void checkConnection()     = 0;
    virtual void tryOpenCom()          = 0;
    virtual void tryCloseCom()         = 0;

    virtual void RGBColorEmit( QRgb rgb ) = 0;

    virtual void captureSound( bool on_off, QString device_name ) = 0;

};

#endif // IWIRINGVIEW_H
