#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uploader.h"
#include "downloader.h"

#include "postjson.h"
#include "getjson.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void progress(qint64 bytesSent, qint64 bytesTotal);
    void finished(bool error, bool aborted, const QString &text);
    void started();

    void downstarted(const QString &filename, qint64 size, const QString &fileurl);
    void downprogress(qint64 bytesReceived, qint64 bytesTotal);
    void downfinished(const QString &error, bool aborted, bool paused);


    void postJsonFinished(const QString &text);

    void getJsonFinished(const QString &error);

private:
    Ui::MainWindow *ui;
    Uploader *_uploader;
    DownLoader *_downloader;

    PostJson *_postJson;
    GetJson *_getJson;
};

#endif // MAINWINDOW_H
