#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class DownLoader : public QObject
{
    Q_OBJECT

public:
    DownLoader(QObject *parent = 0);
    ~DownLoader();

private:
    QNetworkAccessManager *_manager;
    QNetworkReply *_reply;
    QFile *_file;
    QString _filename, _path;

    QString _errorStr;
    QString _papka, _fileurl;
    bool _overwriteFiles;
    QString _redirectLocation;

private slots:
    void headersChanged();
    void dataReady();
    void requestFinished();
    void dataCodUrlReceived(const QString &urlstr);

public slots:
    void download(const QString &urlstr, const QString &folder, bool overwrite);

signals:
    void started(const QString &filename, qint64 size, const QString &fileurl);
    void progress(qint64 bytesReceived, qint64 bytesTotal);
    void finished(const QString &error, bool aborted, bool paused);
};

#endif // DOWNLOADER_H
