#include <QUrl>
#include <QNetworkRequest>
#include "FileDownloader.h"

FileDownloader::FileDownloader(QObject *parent) :
    QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)),
                SLOT(fileDownloaded(QNetworkReply*)));
}

void FileDownloader::download(QString urlStr)
{
    QUrl url(urlStr);
    QNetworkRequest request(url);
    m_WebCtrl.get(request);
}

FileDownloader::~FileDownloader()
{

}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    //emit a signal
    pReply->deleteLater();
    emit downloaded(m_DownloadedData);
}

QByteArray FileDownloader::downloadedData() const
{
    return m_DownloadedData;
}
