#include "postjson.h"

#include <QDebug>

PostJson::PostJson(QObject *parent) :
    QObject(parent)
{
    _reply = 0;
    _manager = new QNetworkAccessManager(this);
}

void PostJson::post(const QString &url, const QJsonObject &jsonObj)
{
    _errorStr.clear();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc(jsonObj);
    QByteArray bytes = doc.toJson();

/*
    request.setRawHeader("User-Agent", "My app name v0.1");
    request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
    request.setRawHeader("Content-Type", "application/json");
*/

    _reply = _manager->post(request, bytes);
    connect(_reply, SIGNAL(finished()), this, SLOT(replyFinished()));
}

void PostJson::replyFinished()
{
    disconnect(_reply, SIGNAL(finished()), this, SLOT(replyFinished()));

    if (_reply->error()>0)
    {
        _errorStr = tr("Network error: %1").arg(QString::number(_reply->error()));
    }
    else
    {
    }
    emit finished(_errorStr);
}
