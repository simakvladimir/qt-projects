#ifndef UPLOADER_H
#define UPLOADER_H

#include <QUrl>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include "qupfile.h"

class Uploader : public QObject
{
    Q_OBJECT
public:
    explicit Uploader(QObject *parent = 0);

signals:
    void progress(qint64 bytesSent, qint64 bytesTotal);
    void finished(bool error, bool aborted, const QString &text);
    void started();

public slots:
    void upload(const QString &siteurl, const QString &filename,  const QString &descr);
private slots:
    void replyFinished();

private:
    QUpFile *_upf;
    QString _siteurl;
    QNetworkReply *_reply;
    QNetworkAccessManager *_manager;

};

#endif // UPLOADER_H
