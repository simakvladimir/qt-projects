#include "downloader.h"
#include <QUrl>
#include <QMessageBox>
#include <QFileInfo>
#include <QTextCodec>

#include <QDebug>

DownLoader::DownLoader(QObject *parent) : QObject(parent)
{
    _manager = new QNetworkAccessManager(this);
    _file = 0;
    _reply = 0;
    _overwriteFiles = false;
}

DownLoader::~DownLoader()
{
}

///////////////////////PRIVATE SLOTS://////////////////////////////////////////////////
void DownLoader::headersChanged()
{
    if (_reply->error()>0)
    {
        _errorStr = tr("Network error: %1").arg(QString::number(_reply->error()));
        return;
    }

    int statuscode = _reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if ((statuscode>=300) && (statuscode<=399))
    {
        _redirectLocation = _reply->rawHeader(QString("location").toLatin1());
        _reply->abort();
        return;
    }

    if (_reply->hasRawHeader(QString("Content-Disposition").toLatin1()))
    {
        QString inf = _reply->rawHeader(QString("Content-Disposition").toLatin1());
        int startpos = inf.indexOf("filename=", 0, Qt::CaseInsensitive);
        if (startpos>=0)
        {
            int len = inf.length()-startpos-QString("filename=").length();
            if (len>0)
            {
                _filename = inf.right(len);
                _filename.remove(QChar('\"'));
            }
        }
    }

    qint64 size = _reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();

    if (!_overwriteFiles)
    {
        while (QFile::exists(_path+_filename))
        {
            _filename.append("_1");
        }
    }

    emit started(_filename, size, _fileurl);
    _file = new QFile(_path+_filename+".part");
    if (!_file->open(QIODevice::ReadWrite))
    {
        _errorStr = tr("Can 't create file %1").arg(_filename);
        _reply->abort();
        return;
    }
}

void DownLoader::dataReady()
{
    if (_reply->error()>0)
    {
        _errorStr = tr("Network error: %1").arg(QString::number(_reply->error()));
        return;
    }
    QByteArray bytes = _reply->readAll();
    if (_file->write(bytes)<0)
    {
        _errorStr = tr("Error writing file %1").arg(_filename);
        _reply->abort();
        return;
    }
}

void DownLoader::requestFinished()
{
    if (!_redirectLocation.isEmpty())
    {
        download(QString(_redirectLocation), _papka, _overwriteFiles);
        return;
    }
    if (_reply->error()>0 && (_errorStr.isEmpty()))
    {
        _errorStr = tr("Network error: %1").arg(QString::number(_reply->error()));
    }
    if (_file)
    {
        _file->close();
        if ((!_errorStr.isEmpty()))
        {
            _file->remove();
        } else
        {
            QString fn = _file->fileName();
            fn = fn.mid(0, fn.size()-5);
            _file->rename(fn);
        }
        delete _file;
    }
    emit finished(_errorStr, false, false);
    _file = 0;
}

void DownLoader::dataCodUrlReceived(const QString &urlstr)
{
    if (urlstr.isEmpty())
    {
        emit finished(tr("Error: Can't receive file URL"), false, false);
        return;
    }
    download(urlstr, _papka, _overwriteFiles);
}
///////////////////////////////////////////////////////////////////////////////////////

//////////////////////PUBLIC SLOTS:////////////////////////////////////////////////////
void DownLoader::download(const QString &urlstr, const QString &folder, bool overwrite)
{
    //isFirst = true;
    _overwriteFiles = overwrite;
    //isAborted = false;
    //isPaused = false;
    _errorStr.clear();
    _redirectLocation.clear();

    QUrl url(urlstr);
    _fileurl = urlstr;
    qDebug() << url.toEncoded();
    //url.setUrl(urlstr.toLatin1());
    if (!url.isValid())
    {
        emit finished(tr("Error: Bad file URL"), false, false);
        return;
    }
    //////filename from url///////////////////////////
    QFileInfo fileinfo(url.path());
    _filename = fileinfo.fileName();
    if (_filename.isEmpty())
    {
        _filename = "index.html";
    }
    if (!folder.isEmpty())
    {
        if (folder.right(1)!="/")
        {
            _path = folder;
            _path.append("/");
        } else
        {
            _path = folder;
        }
    }
    /////////////////////////////////////////////////////

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Wget");
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Connection", "Keep-Alive");

    _reply = _manager->get(request);
    connect(_reply, SIGNAL(metaDataChanged()), this, SLOT(headersChanged()));
    connect(_reply, SIGNAL(readyRead()), this, SLOT(dataReady()));
    connect(_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
    connect(_reply, SIGNAL(finished()), this, SLOT(requestFinished()));
}


///////////////////////////////////////////////////////////////////////////////////////
