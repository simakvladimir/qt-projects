#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setQwtPlot();
    tuneStatusBar();

}

MainWindow::~MainWindow()
{
    delete surf;
    delete grLay;

    delete ui;
    qDebug() << "main win dest";
}

/*!
 * \brief MainWindow::setQwtPlot Установка виджета для отбражения плота
 */
void MainWindow::setQwtPlot()
{
    grLay = new QGridLayout(ui->frame);

    surf = new Qwt3D::SurfacePlot(ui->frame);
    surf->setTitle("SurfacePlot Demo");
    grLay->addWidget(surf,0,0);


}

void MainWindow::tuneStatusBar()
{
    status = new QLabel(ui->statusbar);
    ui->statusbar->addWidget(status,0);
}

void MainWindow::blockWidgets()
{
    ui->pBStart->setEnabled(false);
}

void MainWindow::unblockWidgets()
{
    ui->pBStart->setEnabled(true);
}

void MainWindow::drawPlot(double *Xd, double *Yd, double *Zd, int Nd, int Md)
{
    qDebug() << "DRAW" << Nd << Md;
    QFunc3D func(surf,Xd,Yd,Zd,Nd,Md);
    func.setDomain(-1.5,1.5,-3,3);
    func.setMesh(Nd, Md );
    func.create();

    QStringList labs;
    labs << "freq" << "time" << "Z";
    int num[12] = {0,1,2,0,0,0,1,1,1,2,2,2};
    for (int k=0; k != (int)surf->coordinates()->axes.size(); k++)
    {
        // устанавливаем надпись
        surf->coordinates()->axes[k].setLabelString(labs[num[k]]);
//        surf->coordinates()->axes[k].setLimits(-100,100);
        // количество делений
        surf->coordinates()->axes[k].setMajors(5);  // основных
        surf->coordinates()->axes[k].setMinors(10);  // вспомогательных
    }
}

void MainWindow::setStatusDescription(QString str)
{
    status->setText(str);
}

/*!
 * \brief MainWindow::on_actnOpenFile_triggered Открытие файла
 */
void MainWindow::on_actnOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открытие файла"),
                                                     "/home",
                                                     tr("Sound (*.wav)"));
    if (!fileName.isEmpty())
        emit signalFileName(fileName);

//    blockWidgets();
}

void MainWindow::on_pBStart_clicked()
{
    emit signalStart(4096,0,1);
}
