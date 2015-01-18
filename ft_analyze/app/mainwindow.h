#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QProgressBar>

#include <QDebug>

#include "qfunc3d.h"
#include <qwt3d_surfaceplot.h>
#include <qwt3d_types.h>


#define SCALE_MIN_VAL 1.0
#define SCALE_MAX_VAL 5.0

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setQwtPlot();
    void setQwtAxisLabel(int fetchFreq, double duration);
    void tuneStatusBar();
    void blockWidgets();
    void unblockWidgets();

    void setStatusDescription(QString str);
    void setTimeDuration(QString timeStr);
    void drawPlot(double *Xd,
                  double *Yd,
                  double *Zd,
                  int Nd,
                  int Md , int fetchFreq, int samples);

    int getCurrentDev();

    void setDevDesc(QStringList list);
    void resetScreen();

private slots:
    void on_actnOpenFile_triggered();

    void on_pBStart_clicked();

    void on_vSliderScale_sliderReleased();

    void on_cBoxDev_currentIndexChanged(int index);

public slots:
    void setProgressBar(int value);

signals:
    void signalFileName(QString);
    void signalStart(int, int);
    void signalDeviceChanged(int);

private:
    Ui::MainWindow *ui;
    QLabel *status;
//    QProgressBar *progressBar;

    QGridLayout *grLay;
    Qwt3D::SurfacePlot *surf;

    QFunc3D *func;

    double scale;
    double freq;
    double duration;
};

#endif // MAINWINDOW_H
