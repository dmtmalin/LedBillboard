#include <QtDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTimer>
#include "model/playlist.h"
#include "model/mediacontent.h"
#include "model/playlistcollection.h"
#include "service/apiservice.h"
#include "settings.h"
#include "playlistcollectionservice.h"

PlaylistCollectionService::PlaylistCollectionService(QObject *parent) : QObject(parent)
{
    this->downloadCounter = 0;
    connect(apiService::Instance(), SIGNAL(loginSuccess()), SLOT(slotLoginSuccess()));
    connect(apiService::Instance(), SIGNAL(loginFailure()), SLOT(slotLoginFailure()));
    connect(apiService::Instance(), SIGNAL(allPlaylistSuccess(QByteArray&)),
            SLOT(slotAllPlaylistSuccess(QByteArray&)));
    connect(apiService::Instance(), SIGNAL(allPlaylistFailure()), SLOT(slotAllPlaylistFailure()));
    connect(apiService::Instance(), SIGNAL(downloadFinished()), SLOT(slotDownloadFinished()));
}

PlaylistCollectionService::~PlaylistCollectionService()
{
    if (this->playlistCollection != NULL) {
        delete this->playlistCollection;
    }
}

void PlaylistCollectionService::loadFromService()
{
    qInfo() << "---Start load playlist collection from service---";
    MyCookieJar *cookie = apiService::Instance()->getCookie();
    if(cookie->isEmpty()) {
        apiService::Instance()->login();
    }
    else {
        QString board = settings::Instance()->getValue(Settings::BOARD);
        apiService::Instance()->allPlaylist(board);
    }
}

void PlaylistCollectionService::DownloadMediaFiles()
{
    qInfo() << "---Start sync media files.---";
    if (this->playlistCollection == NULL) {
        qCritical() << "---Playlist collection is NULL! Finish sync media files.---";
        return;
    }
    QList<MediaContent *> mediaContent = this->playlistCollection->getAllMedia();
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
        emit successDownloadMediaFiles();
    }
}

/*
 * SLOTS
*/

void PlaylistCollectionService::slotLoginSuccess()
{
    QString board = settings::Instance()->getValue(Settings::BOARD);
    apiService::Instance()->allPlaylist(board);
}

void PlaylistCollectionService::slotLoginFailure()
{    
    int retry = settings::Instance()->getValue(Settings::RETRY).toInt();
    int retrySec = retry / 1000;
    qInfo() << QString("Retry login in %1 sec.").arg(retrySec);
    QTimer::singleShot(retry, apiService::Instance(), apiService::Instance()->login);
}

void PlaylistCollectionService::slotAllPlaylistSuccess(QByteArray &arr)
{
    QJsonDocument doc = QJsonDocument::fromJson(arr);
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        QJsonArray edges = obj
                        ["data"].toObject()
                        ["allPlaylist"].toObject()
                        ["edges"].toArray();
        if (edges.isEmpty()) {
            qWarning() << "Playlist data is empty.";
        }
        else {
            if (this->playlistCollection != NULL) {
                delete this->playlistCollection;
            }
            this->playlistCollection = PlaylistCollection::fromJson(edges);
        }
    }
    else {
        qWarning() << "Cant't parse playlist json data.";
    }
    int countCollection = 0;
    if(this->playlistCollection != NULL) {
        countCollection = this->playlistCollection->count();
    }
    qInfo() << QString("---Finish load %1 playlist collection from service---").arg(
                   countCollection);
    emit successLoadFromService();
}

void PlaylistCollectionService::slotAllPlaylistFailure()
{
    apiService::Instance()->getCookie()->clear();
    int retry = settings::Instance()->getValue(Settings::RETRY).toInt();
    int retrySec = retry / 1000;
    qWarning() << QString("---Retry load playlist collection in %1 sec. Relogin.---").arg(
                      retrySec);
    QTimer::singleShot(retry, this, loadFromService);
}

void PlaylistCollectionService::slotDownloadFinished()
{
    --this->downloadCounter;
    if (this->downloadCounter == 0) {
        qInfo() << "---Finish sync media files---.";
        emit successDownloadMediaFiles();
    }
}
