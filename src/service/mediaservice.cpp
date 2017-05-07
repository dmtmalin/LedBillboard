#include <QtDebug>
#include <QList>
#include <QFile>
#include "service/apiservice.h"
#include "service/playlistcollectionservice.h"
#include "model/mediacontent.h"
#include "model/playlistcollection.h"
#include "mediaservice.h"

MediaService::MediaService(QObject *parent) : QObject(parent)
{
    this->downloadCounter = 0;
    connect(apiService::Instance(), SIGNAL(downloadFinished()), SLOT(slotDownloadFinished()));
}

void MediaService::DownloadMediaFiles()
{
    qInfo() << "---Start sync media files.---";
    QList<MediaContent *> mediaContent = playlistCollectionService::Instance()
            ->getCollection()
            ->getAllMedia();
    foreach (MediaContent *media, mediaContent) {
        QString url = media->getUrl();
        QString filenameToSave = media->getFileName();
        if(QFile::exists(filenameToSave)) {
            qInfo() << QString("Media file %1 allready exists. Skip download.").arg(
                           filenameToSave);
        }
        else {
            ++this->downloadCounter;
            apiService::Instance()->downloadFile(url, filenameToSave);
        }
    }
    if(this->downloadCounter == 0) {
        qInfo() << "---Finish sync media files. Nothing sync.---";
        emit finishedDownloadMediaFiles();
    }

}

void MediaService::slotDownloadFinished()
{
    --this->downloadCounter;
    if (this->downloadCounter == 0) {
        qInfo() << "---Finish sync media files---.";
        emit finishedDownloadMediaFiles();
    }
}
