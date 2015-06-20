#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _uploader(new Uploader),
    _downloader(new DownLoader),
    _postJson(new PostJson),
    _getJson(new GetJson)
{
    ui->setupUi(this);

    connect(_uploader, SIGNAL(started()), this, SLOT(started()));
    connect(_uploader, SIGNAL(progress(qint64,qint64)), this, SLOT(progress(qint64,qint64)));
    connect(_uploader, SIGNAL(finished(bool,bool,QString)), this, SLOT(finished(bool,bool,QString)));

    connect(_downloader, SIGNAL(started(QString,qint64,QString)), this, SLOT(downstarted(QString,qint64,QString)));
    connect(_downloader, SIGNAL(progress(qint64,qint64)), this, SLOT(downprogress(qint64,qint64)));
    connect(_downloader, SIGNAL(finished(QString,bool,bool)), this, SLOT(downfinished(QString,bool,bool)));

    connect(_postJson, SIGNAL(finished(QString)), this, SLOT(postJsonFinished(QString)));

    connect(_getJson, SIGNAL(finished(QString)), this, SLOT(getJsonFinished(QString)));

//    _uploader->upload("http://192.168.0.105",
//                      "E:/Магистратура/диплом/uzfi/диплом/01_sources/01_sources/_build/app/project/Отчеты/Отчет_дата_03_02_15_время_44_23_54.pdf",
//                      "error");

//    _downloader->download("http://192.168.0.105/content/reports/Отчет_дата_03_02_15_время_14_46_53.pdf",
//                          "E:/",
//                          true);

    QJsonObject json;
    json["id"] = QString("test");
    json["name"] = QString("fgdfgdf");
    _postJson->post("http://192.168.0.105/auth/teststart", json);

    _getJson->get("http://192.168.0.105/auth/teststatus");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::progress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug() << "[MainWindow::progress]" << bytesSent << bytesTotal;
}

void MainWindow::finished(bool error, bool aborted, const QString &text)
{
    qDebug() << "[MainWindow::finished]" << error << text;
}

void MainWindow::started()
{
    qDebug() << "[MainWindow::started]";
}


void MainWindow::downstarted(const QString &filename, qint64 size, const QString &fileurl)
{
    qDebug() << "[MainWindow::downstarted]" << filename << size << fileurl;
}

void MainWindow::downprogress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << "[MainWindow::downprogress]" << bytesReceived << bytesTotal;
}

void MainWindow::downfinished(const QString &error, bool aborted, bool paused)
{
    qDebug() << "[MainWindow::downprogress]" << error << aborted << paused;
}

void MainWindow::postJsonFinished(const QString &text)
{
    qDebug() << "[MainWindow::postJsonFinished]" << text;
}

void MainWindow::getJsonFinished(const QString &error)
{
    qDebug() << "[MainWindow::getJsonFinished]" << error << _getJson->json();
}
