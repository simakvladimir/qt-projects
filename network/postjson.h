#ifndef POSTJSON_H
#define POSTJSON_H

#include <QObject>

#include <QUrl>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QJsonObject>
#include <QJsonDocument>

class PostJson : public QObject
{
    Q_OBJECT
public:
    explicit PostJson(QObject *parent = 0);

    QString error() const { return _errorStr; }

signals:
    void finished(const QString &text);

public slots:
    void post(const QString &url, const QJsonObject &jsonObj);

private slots:
    void replyFinished();

private:
    QString _errorStr;

    QNetworkReply *_reply;
    QNetworkAccessManager *_manager;
};

#endif // POSTJSON_H
