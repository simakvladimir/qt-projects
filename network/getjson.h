#ifndef GETJSON_H
#define GETJSON_H

#include <QObject>

#include <QUrl>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QJsonObject>
#include <QJsonDocument>

class GetJson : public QObject
{
    Q_OBJECT
public:
    explicit GetJson(QObject *parent = 0);

    QString error() const { return _errorStr; }
    QJsonObject json() const { return _json; }

signals:
    void finished(const QString &error);

public slots:
    void get(const QString &url);
private slots:
    void requestFinished();

private:
    QString _errorStr;
    QNetworkReply *_reply;
    QNetworkAccessManager *_manager;

    QJsonObject _json;
};

#endif // GETJSON_H
