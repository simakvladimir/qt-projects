#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>

#include "qfunc3d.h"
#include <qwt3d_surfaceplot.h>

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
    void tuneStatusBar();
    void blockWidgets();
    void unblockWidgets();

    void setStatusDescription(QString str);
    void drawPlot(double *Xd,
                  double *Yd,
                  double *Zd,
                  int Nd,
                  int Md );

private slots:
    void on_actnOpenFile_triggered();

    void on_pBStart_clicked();

signals:
    void signalFileName(QString);
    void signalStart(int, int, int);

private:
    Ui::MainWindow *ui;
    QLabel *status;

    QGridLayout *grLay;
    Qwt3D::SurfacePlot *surf;
};

#endif // MAINWINDOW_H
