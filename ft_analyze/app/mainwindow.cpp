#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    func(NULL),
    scale(1.0)
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
    grLay = new QGridLayout(ui->qwtPlot);

    surf = new Qwt3D::SurfacePlot(ui->qwtPlot);
    surf->setTitle("Спектограмма");
    Qwt3D::RGBA rgb = Qwt3D::Qt2GL(QColor(Qt::darkBlue));
    surf->setMeshColor(rgb);
    grLay->addWidget(surf,0,0);

}

void MainWindow::setQwtAxisLabel(int fetchFreq, double duration)
{
    QStringList labs;
    labs << "Частота, Гц" << "Время, с" << "Амп.";
    bool enable[3] = {true,true,false};
    double range[3] = {(double)fetchFreq,duration,2};

    int num[12]   = {0,1,2,0,0,0,1,1,1,2,2,2};
    for (int k=0; k != (int)surf->coordinates()->axes.size(); k++)
    {
        // устанавливаем надпись
        surf->coordinates()->axes[k].setLabelString(labs[num[k]]);
        surf->coordinates()->axes[k].setLimits(0, range[num[k]]);

        surf->coordinates()->axes[k].setNumbers(enable[num[k]]);
        surf->coordinates()->axes[k].setLabel(enable[num[k]]);
        // количество делений
        surf->coordinates()->axes[k].setMajors(5);  // основных
        surf->coordinates()->axes[k].setMinors(10);  // вспомогательных
    }
}

void MainWindow::tuneStatusBar()
{
//    progressBar = new QProgressBar(ui->statusbar);
//    ui->statusbar->addWidget(progressBar,0);
//    progressBar->setFixedWidth(300);
//    progressBar->setMaximum(99);

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

void MainWindow::drawPlot(double *Xd, double *Yd, double *Zd, int Nd, int Md, int fetchFreq, int samples)
{
    qDebug() << "DRAW" << Nd << Md;
    if (func)
        delete func;

    freq = fetchFreq / 2;
    duration = (1 * samples )/ (double)fetchFreq;

    func = new QFunc3D(surf,Xd,Yd,Zd,Nd,Md);
    func->setDomain(-1.5,1.5,-3,3);
    func->setMesh(Nd, Md );
    func->setScale(scale);
    func->create();

    setQwtAxisLabel(freq,duration);
    surf->update();
}

int MainWindow::getCurrentDev()
{
    return ui->cBoxDev->currentIndex();
}

void MainWindow::setDevDesc(QStringList list)
{
    ui->lblDevType->setText(list.at(0));
    ui->lcdFreq->display(list.at(1));
    ui->lcdCores->display(list.at(2));
}

void MainWindow::resetScreen()
{
    ui->lblTimeDuration->clear();

}

void MainWindow::setStatusDescription(QString str)
{
    status->setText(str);
}

void MainWindow::setTimeDuration(QString timeStr)
{
    ui->lblTimeDuration->setText(timeStr);
}

/*!
 * \brief MainWindow::on_actnOpenFile_triggered Открытие файла
 */
void MainWindow::on_actnOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открытие файла"),
                                                     QApplication::applicationDirPath(),
                                                     tr("Sound (*.wav)"));
    if (!fileName.isEmpty())
        emit signalFileName(fileName);

}

void MainWindow::on_pBStart_clicked()
{
    bool ok;
    setStatusDescription("Преобразование");
    resetScreen();

    int winSize = ui->cBoxWinSize->currentText().toInt(&ok);

    emit signalStart(winSize,1);
}

void MainWindow::setProgressBar(int value)
{
    ui->progressBar->setValue(value+1);
}

void MainWindow::on_vSliderScale_sliderReleased()
{
    scale = SCALE_MIN_VAL + ( SCALE_MAX_VAL - SCALE_MIN_VAL )
            / ( ui->vSliderScale->maximum() -  ui->vSliderScale->minimum() ) * ui->vSliderScale->value();

    qDebug() << "scale" << scale;

    if (func){
        func->setScale(scale);
        func->create();
        setQwtAxisLabel(freq, duration);
        surf->update();
    }

}

void MainWindow::on_cBoxDev_currentIndexChanged(int index)
{
    emit signalDeviceChanged(index);
}
