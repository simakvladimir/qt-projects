#ifndef EQUALIZER_H
#define EQUALIZER_H

#include <QWidget>
#include <QPainter>
#include "buffer/common.h"

class Equalizer : public QWidget
{
    Q_OBJECT
public:
    explicit Equalizer(QWidget *parent = 0);
    
private:
    QImage *image;
    QPoint  wd_size;

    QVector<float> array_of_values;

    int     band_count;
    int     width_between_band_in_px;
    int     max_value;
    int     scale;
    int     wgt_height;
    int     top_border;
    int     bottom_border;
    int     global_scale;
signals:
    
protected:
    QSize sizeHint() const;
    void paintEvent(QPaintEvent *);
public slots:
    void equalizer_update_slot( const MyArray &bb );
    
};

#endif // EQUALIZER_H
