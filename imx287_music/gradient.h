#ifndef GRADIENT_H
#define GRADIENT_H

#include <QWidget>
#include <QPainter>

class Gradient : public QWidget
{
    Q_OBJECT

protected:
//    bool eventFilter(QObject *o, QEvent *e);
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;
    void mousePressEvent( QMouseEvent * event );
//    QSize minimumSizeHint() const;

public:
    explicit Gradient(QWidget *parent = 0, QPoint size = QPoint(0,0));

    /* Cobfigure methodes */
    void     SetBackGroundColor( QColor color ){ bg_color = color; };
    void     SetWidgetSize( QPoint point )     { wd_size  = point; };




signals:
    void RGBColor( QRgb color );
    
public slots:
    
   private:
       QImage   *image;

QPoint xy_mouse;

       QColor  bg_color;
       QPoint  wd_size;
       qint32  big_radius;
       qint32  med_radius;
       qreal   hue;
};

#endif // GRADIENT_H
