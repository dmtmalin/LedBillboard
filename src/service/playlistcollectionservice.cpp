#include <QtDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "model/playlist.h"
#include "model/mediacontent.h"
#include "model/playlistcollection.h"
#include "service/apiservice.h"
#include "service/timingservice.h"
#include "settings.h"
#include "playlistcollectionservice.h"

PlaylistCollectionService::PlaylistCollectionService(QObject *parent) : QObject(parent)
{
    this->playlistCollection = new PlaylistCollection();
    connect(apiService::Instance(), SIGNAL(loginSuccess()), SLOT(slotLoginSuccess()));
    connect(apiService::Instance(), SIGNAL(loginFailure()), SLOT(slotLoginFailure()));
    connect(apiService::Instance(), SIGNAL(allPlaylistSuccess(QByteArray&)),
            SLOT(slotAllPlaylistSuccess(QByteArray&)));
    connect(apiService::Instance(), SIGNAL(allPlaylistFailure()), SLOT(slotAllPlaylistFailure()));
}

PlaylistCollectionService::~PlaylistCollectionService()
{
    delete this->playlistCollection;
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

PlaylistCollection *PlaylistCollectionService::getCollection()
{
    return this->playlistCollection;
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
    timingService::Instance()->retryLogin();
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
            this->playlistCollection->updateFromJson(edges);
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
    timingService::Instance()->retryLoadPlaylistCollection();
}
