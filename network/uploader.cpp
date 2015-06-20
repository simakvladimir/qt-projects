#include "uploader.h"

Uploader::Uploader(QObject *parent) :
    QObject(parent)
{
    _upf = 0;
    _reply = 0;
    _manager = new QNetworkAccessManager(this);
}

void Uploader::upload(const QString &siteurl, const QString &filename, const QString &descr)
{
    QByteArray boundaryRegular(QString("--"+QString::number(qrand(), 10)).toLatin1());
    QByteArray boundary("\r\n--"+boundaryRegular+"\r\n");
    QByteArray boundaryLast("\r\n--"+boundaryRegular+"--\r\n");

    QUrl url(QString(siteurl + "/auth/upload"));
    QNetworkRequest request(url);

    _siteurl = siteurl;

    request.setRawHeader("Host", url.host().toLatin1());
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows; U; Windows NT 5.1; ru; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)");
    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Language", "ru,en-us;q=0.7,en;q=0.3");
    request.setRawHeader("Accept-Encoding", "gzip,deflate");
    request.setRawHeader("Accept-Charset", "windows-1251,utf-8;q=0.7,*;q=0.7");
    request.setRawHeader("Keep-Alive", "300");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("Referer", siteurl.toLatin1());
    request.setRawHeader("Content-Type", QByteArray("multipart/form-data; boundary=").append(boundaryRegular));

    QByteArray mimedata1("--"+boundaryRegular+"\r\n");
    mimedata1.append("Content-Disposition: form-data; name=\"action\"\r\n\r\n");
    mimedata1.append("file_upload");
    mimedata1.append(boundary);
    mimedata1.append("Content-Disposition: form-data; name=\"sfile\"; filename=\""+filename.toUtf8()+"\"\r\n");
    mimedata1.append("Content-Type: application/octet-stream\r\n\r\n");

    QByteArray mimedata2(boundary);
    mimedata2.append("Content-Disposition: form-data; name=\"description\"\r\n\r\n");
    mimedata2.append(descr.toUtf8());
    mimedata2.append(boundary);
    mimedata2.append("Content-Disposition: form-data; name=\"agree\"\r\n\r\n");
    mimedata2.append("1");
    mimedata2.append(boundaryLast);

    _upf = new QUpFile(filename, mimedata1, mimedata2, this);
    if (_upf->openFile())
    {
        _reply = _manager->post(request, _upf);
        connect(_reply, SIGNAL(uploadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
        connect(_reply, SIGNAL(finished()), this, SLOT(replyFinished()));
        emit started();
    } else
    {
        emit finished(true, false, tr("Error: can't open file %1").arg(filename));
    }
}

void Uploader::replyFinished()
{
    if (_upf)
    {
        _upf->close();
        delete _upf;
        _upf = 0;
    }
    disconnect(_reply, SIGNAL(uploadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
    disconnect(_reply, SIGNAL(finished()), this, SLOT(replyFinished()));

/*    if (isAborted)
    {
        emit finished(false, true, QString());
    }
    else*/ if (_reply->error()>0)
    {
        emit finished(true, false, tr("Network error: %1").arg(QString::number(_reply->error())));
    }
    else
    {
      //  QString loc = _reply->rawHeader("Location");
      //  if (!loc.isEmpty())
            emit finished(false, false, _siteurl);
      //  else
      //      emit finished(true, false, tr("Error: %1").arg(_reply->errorString()));
    }
}
