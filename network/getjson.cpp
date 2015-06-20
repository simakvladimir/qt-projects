#include "getjson.h"
#include <QDebug>

GetJson::GetJson(QObject *parent) :
    QObject(parent)
{
    _reply = 0;
    _manager = new QNetworkAccessManager(this);
}

void GetJson::get(const QString &url)
{
    QNetworkRequest request(url);

    _errorStr.clear();
    _reply = _manager->get(request);
    connect(_reply, SIGNAL(finished()), this, SLOT(requestFinished()));
}

void GetJson::requestFinished()
{
    if (_reply->error()>0)
    {
        _errorStr = tr("Network error: %1").arg(QString::number(_reply->error()));
    } else {

        QJsonDocument jsonResponse = QJsonDocument::fromJson(_reply->readAll());
        _json = jsonResponse.object();

    }
    emit finished(_errorStr);
}
