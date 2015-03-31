#include <QDebug>
#include "diodeview.h"
#include "ui_diodeview.h"
#include "gradient.h"
#include "eq/equalizer.h"
/*
 *  Com port include
 */
#include "comport\src\qextserialenumerator.h"
#include <QtCore/QList>

/*!
    \class DiodeView

    Представление (View) в триаде MVP расчета электропроводки.
*/

DiodeView::DiodeView(QWidget *parent)
    : QWidget(parent), ui(new Ui::DiodeView),isOpen(false)
{

    ui->setupUi(this);

    Gradient *grad = new Gradient(0, QPoint(150,150) );

    connect(grad,SIGNAL( RGBColor( QRgb ) ),this, SLOT( color_changed( QRgb ) ));


    QGridLayout *test = new QGridLayout();
    test->addWidget(grad);
    ui->color_panel->addLayout(test);
//grad->show();

//    setFixedSize(size());

    eq = new Equalizer( this );
    ui->eq_layot->addWidget( eq );

//    ui->eq_layot->setSizeConstraint( 1 );

    /* Create list of avaible COM-ports in system */
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    foreach (QextPortInfo info, ports) {
        ui->com_number->addItem( info.portName );
     }

    ui->set_speed->setEnabled(isOpen);
}

DiodeView::~DiodeView()
{
    delete ui;
}

/**********************************************************************************************
 *
 ***********************************************************************************************/

void DiodeView::on_set_speed_clicked()
{
    emit checkConnection();
}

void DiodeView::on_open_com_clicked()
{
    isOpen ^= true;
    ui->set_speed->setEnabled(isOpen);
    if (isOpen){ ui->open_com->setText(tr("Закрыть"));emit tryOpenCom();}
    else       { ui->open_com->setText(tr("Открыть"));
        emit tryCloseCom();}

}


/*
 *  Methods for red/green indication
 */
void DiodeView::connection_state( bool error )
{
    if ( error )
        ui->ind_connect->setStyleSheet("border-radius: 7px; background-color: red;");
    else
        ui->ind_connect->setStyleSheet("border-radius: 7px; background-color: green;");
}

void DiodeView::open_com_state( bool error )
{
    if ( error )
        ui->ind_open->setStyleSheet("border-radius: 7px; background-color: red;");
    else
        ui->ind_open->setStyleSheet("border-radius: 7px; background-color: green;");
}


/*
 *  Get current parameters
 */
QString DiodeView::getCurrentPortName()
{
    return ui->com_number->currentText();
}

QString DiodeView::getCurrentSpeed()
{
    return ui->speed_value->currentText();
}


/* Color change */
void DiodeView::color_changed( QRgb color ){
    emit RGBColorEmit( color );
}

void DiodeView::update_sound_devices(QHash<QString, int> devices){
    foreach (QString key, devices.keys()) {
        ui->sound_devices->addItem( key );
    }
}

Equalizer *DiodeView::get_eq()
{
    return eq;
}

/*
 *  Capture sound from sound car
 */
void DiodeView::on_capture_sound_clicked()
{
    emit captureSound( ui->capture_sound->isChecked(), ui->sound_devices->currentText() );
}
