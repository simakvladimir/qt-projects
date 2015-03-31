#include "equalizer.h"

#include <QDebug>

Equalizer::Equalizer(QWidget *parent) :
    QWidget(parent),
    wgt_height( height() )
{

//    setBaseSize(10,10);
//    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    image = new QImage( sizeHint(), QImage::Format_ARGB32);

    // eq band count
    band_count               = 9;
    width_between_band_in_px = 5;


    scale                    = 10;

    top_border               = 1;
    bottom_border            = 3;

    global_scale             = 50;


    max_value                = 60 + top_border;

    array_of_values.append( 5 );
    array_of_values.append( 3 );
    array_of_values.append( 1 );
    array_of_values.append( 1 );
    array_of_values.append( 30 );
    array_of_values.append( 10 );
    array_of_values.append( 11 );
    array_of_values.append( 12 );
    array_of_values.append( 4 );

    update();
}

QSize Equalizer::sizeHint() const {
//    return QSize(400,400);
    return QSize( dynamic_cast<QWidget*>( parent() )->geometry().width(), dynamic_cast<QWidget*>( parent() )->geometry().height() );
}

void Equalizer::paintEvent(QPaintEvent *)
{
    int   width_band = geometry().width() / array_of_values.count();
    float scale = height() / ( max_value );

    QPainter painter( this );
//    image->scaled( dynamic_cast<QWidget*>( parent() )->geometry().width(),
//                   dynamic_cast<QWidget*>( parent() )->geometry().height(),
//                   Qt::IgnoreAspectRatio);
    qDebug() << " 223123 "<< image->size() << dynamic_cast<QWidget*>( parent() )->geometry().size();

    painter.drawImage(0,0,(*image));
    //fill background
    painter.fillRect( 0, 0, this->width(),this->height(),QBrush(Qt::black) );

    painter.setBrush( QColor(Qt::white) );

    int   indent       = width_between_band_in_px / 2;
    int   counter = 0;
    foreach (float temp_val, array_of_values) {

        temp_val *= global_scale;
        float validate_value = temp_val > max_value ? max_value: temp_val;

        int x = indent + counter * width_band;
        int y = height() - validate_value * scale - bottom_border;
        int rec_h = validate_value * scale;
        int rec_w = width_band - width_between_band_in_px;
        counter++;

        painter.drawRect( x,y, rec_w, rec_h );

    }
//    QRectF rectangle(this->width()/2, this->height()/2, this->width()/10,this->height()/20 );
//    QRectF rectangle1(10.0, 80.0, this->width()/10,this->height()/20 );



//    painter.drawRoundedRect(rectangle, 5.0, 5.0);
//    painter.setBrush(QColor(Qt::red));
//    painter.drawRoundedRect(rectangle1, 5.0, 5.0);
  //  painter.drawEllipse(QPoint( 10, 10),5,5);

    /* painter.setBrush(QColor(0,0,0));

     painter.drawRect( 10, 10, 85, 35 );
     painter.drawRoundRect( 10, 55, 85, 35 );

     QRect rect( 105, 10, 85, 35 );

     painter.drawRoundRect( rect );
     painter.drawRect( rect.translated( 0, 45 ) );
*/

}

void Equalizer::equalizer_update_slot(const MyArray &bb)
{
    array_of_values.clear();
    array_of_values = bb;
//    qDebug() << "1111111111111111111111111111111111111111111111111111111111111111111111";
//    qDebug() << bb;
    update();
}
