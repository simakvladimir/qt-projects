#include "diodepresenter.h"
#include "idiodeview.h"
#include "eq/equalizer.h"
#include "buffer/common.h"

#include <QDebug>
/*!
    \class WiringPresenter
*/

DiodePresenter::DiodePresenter(IDiodeView *view, QObject *parent)
    : QObject(parent), m_model(new DiodeModel(this) ),
                       m_view(view),
                       port_audio( new PortAudioWrapper( this, &fifo_buf ) ),
                       fftw_thr( new FFTW_Thread( this, &fifo_buf ) )

{
    QObject *view_obj = dynamic_cast<QObject*>(m_view);
    QObject::connect(view_obj, SIGNAL(checkConnection()),
                     this, SLOT(startSetConnection()));
    QObject::connect(view_obj, SIGNAL(tryOpenCom()),
                     this, SLOT(openComPort()));
    QObject::connect(view_obj, SIGNAL(tryCloseCom()),
                     this, SLOT(closeComPort()));

    QObject::connect(view_obj, SIGNAL(RGBColorEmit( QRgb )),
                     this, SLOT(ColorChanged( QRgb )));
    QObject::connect(view_obj, SIGNAL(RGBColorEmit( QRgb )),
                     this, SLOT(ColorChanged( QRgb )));

    QObject::connect(view_obj, SIGNAL(captureSound( bool, QString )),
                     this, SLOT(SetCaptureSound( bool, QString )));



    Equalizer *eq = dynamic_cast<Equalizer*>(m_view->get_eq());
    QObject::connect(fftw_thr, SIGNAL(fftw_complete(MyArray)),
                     m_view->get_eq(), SLOT(equalizer_update_slot(MyArray)),Qt::QueuedConnection);


    QObject::connect( fftw_thr, SIGNAL(fftw_complete(MyArray)),
                      this, SLOT(SendColorOnBoard(MyArray)));



     /* Port Audio test section */
//     qDebug() << " Port Audio output "<< port_audio->get_device_count();
     sound_devices = port_audio->get_devices_names();
     m_view->update_sound_devices( sound_devices );



//    refreshView();
}


void DiodePresenter::refreshView() const
{
    switch( m_model->error )
    {
        case DiodeModel::OPEN_SUCCESS:  m_view->open_com_state(false); break;
        case DiodeModel::OPEN_FAILED:   m_view->open_com_state(true);  break;
        default: break;
    }
}

void DiodePresenter::openComPort()
{
    bool result;
    m_model->CreateComPort( m_view->getCurrentPortName() );

    m_model->ConfigureComPort( BaudRateType(COM_MIN_SPEED) );
//     m_model->OpenComPort();
    emit emitOpenComSignal( result );

    //TODO made process of error
    m_model->error = (DiodeModel::com_return)result;
    refreshView();
}

void DiodePresenter::closeComPort()
{
//    m_model->ConfigureComPort( BaudRateType(COM_MIN_SPEED) );
    m_model->CloseComPort();
    m_model->error =  DiodeModel::OPEN_FAILED;
    refreshView();
}


void DiodePresenter::startSetConnection()
{
    QByteArray temp;//TODO

    int speed  =  m_view->getCurrentSpeed().toInt();

    temp.resize(4);
    /* Create array with param */
    temp[0] = PARAMETERS - 1;
    temp[1] = speed >> 16;
    temp[2] = speed >> 8;
    temp[3] = speed;

    emit emitSendComSignal( m_model->CreateCommand(DiodeModel::SET_SPEED, temp ) );
//    m_model->ConfigureComPort( BaudRateType( m_view->getCurrentSpeed().toInt() ) );

//    m_model->WriteDataOnCom(  );
    refreshView();
}

void DiodePresenter::ColorChanged( QRgb rgb )
{
    QByteArray param_array;

    param_array.resize(4);
    /* Create array with param */
    param_array[0] = PARAMETERS - 1;
    param_array[1] = char( QColor( rgb ).red()   );
    param_array[2] = char( QColor( rgb ).green() );
    param_array[3] = char( QColor( rgb ).blue()  );

    emit emitSendComSignal( m_model->CreateCommand(DiodeModel::COLOR, param_array ) );
//    m_model->WriteDataOnCom( m_model->CreateCommand(DiodeModel::COLOR, param_array ) );


}


void DiodePresenter::SetCaptureSound(bool on_off, QString device_name){

    if ( !on_off ) {
        port_audio->capture_audio_stream_stop();
    }
    if (  on_off ) {
        int device_index = sound_devices.value( device_name );
        port_audio->configure_stream( device_index, -1 );
        port_audio->capture_audio_stream_start();
    }

}

void DiodePresenter::SendColorOnBoard(MyArray data)
{
    QVector<float> array_of_values;
    array_of_values = data;

    int start;
    double value,summa = 0;
    int i=0;
    int size = data.size() / 6;
    // red
    start = 1;
    for ( i = start; i < start + size; i++ )
    {
        summa += data[i];
    }
    value = summa / (size);

    int red_color = value / 10.0 * 255;

    start = i;
    summa = 0;
    for ( i = start; i < start + size; i++ )
    {
        summa += data[i];
    }
    value = summa / (size);

    int green_color = value / 10.0 * 255;

    start = i;
    summa = 0;
    for ( i = start; i < start + size; i++ )
    {
        summa += data[i];
    }
    value = summa / (size);

    int blue_color = value / 10.0 * 255;

    qDebug() << "RED=" <<red_color;
    qDebug() << "GREEN=" <<green_color;
    qDebug() << "BLUE=" <<blue_color;

    ColorChanged( qRgb(red_color, green_color, blue_color) );

}
