#include "gradient.h"
#include <QEvent>
#include <QtGui>
#include <math.h>

/*
 * Constructor
 */
Gradient::Gradient(QWidget *parent, QPoint size ) :
    QWidget(parent), bg_color(Qt::white), wd_size( size ), hue( 0 ), xy_mouse( QPoint( 0,0 ) )
{
//    setLineWidth(3);
//    painter =new  QPainter(this);

    setBaseSize(wd_size.x(),wd_size.y());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    image = new QImage(this->sizeHint(), QImage::Format_ARGB32);

    big_radius = wd_size.x() < wd_size.y() ?  wd_size.x() : wd_size.y();
    med_radius = big_radius / 1.5;

    update();

}


void Gradient::paintEvent(QPaintEvent *)
{
    qreal rad,angle;
    QColor color;

    //fill widget's background
    //image->fill(bg_color);
    //color map 4 bytes * count of pixels
    unsigned int * pix = (unsigned int *) image->bits();

    //int radMax = 100;
    for (int x = 0; x <  big_radius; ++x) {
        for (int y = 0; y <  big_radius; ++y) {
            qreal xf = x - big_radius;
            qreal yf = big_radius - y;
            rad = sqrt(xf * xf + yf * yf) / big_radius;
            if (rad > 1.0) continue;
                angle = (1.0 - atan2(yf, xf) / M_PI) ;
            if (angle < 0 || angle > 1) continue;

            rad = sqrt(xf * xf + yf * yf) / med_radius;

            if ( rad > 1.0 )
                color.setHsvF(angle*2.f, 1.0, 1.0);
            else
                color.setHslF(hue, 1, angle*2.f);

            pix[(y + wd_size.y() - big_radius)* wd_size.x() + x + ( wd_size.x() - big_radius) ] = color.rgba();
         }
    }

//    QImage image
    QPainter painter( this );
    painter.drawImage(0,0,(*image));
    painter.drawEllipse(xy_mouse,5,5);

}

QSize Gradient::sizeHint() const {
    return QSize(wd_size.x(),wd_size.y());
}


void Gradient::mousePressEvent( QMouseEvent * event )
{
    QPoint pos = event->pos();

    qreal rad;
    qreal xf = wd_size.x() - pos.x();
    qreal yf = wd_size.y() - pos.y();
    rad = sqrt(xf * xf + yf * yf) / big_radius;

    if ( rad > 1 ) return;

    rad = sqrt(xf * xf + yf * yf) / med_radius;

    if ( rad < 1 ) {

        emit RGBColor( image->pixel( pos.x(), pos.y() ) );

    } else {

        hue = atan2(yf, xf) / M_PI * 2 ;

        xy_mouse = pos;

    }
    update();
}

//QSize Gradient::minimumSizeHint() const {
//    return QSize(100,100);
//}
