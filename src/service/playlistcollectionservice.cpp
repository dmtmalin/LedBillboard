#include <QtDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "model/playlistcollection.h"
#include "service/apiservice.h"
#include "settings.h"
#include "playlistcollectionservice.h"

PlaylistCollectionService::PlaylistCollectionService(QObject *parent) : QObject(parent)
{
    connect(apiService::Instance(), SIGNAL(loginSuccess()), SLOT(slotLoginSuccess()));
    connect(apiService::Instance(), SIGNAL(loginFailure()), SLOT(slotLoginFailure()));
    connect(apiService::Instance(), SIGNAL(allPlaylistSuccess(QByteArray&)),
            SLOT(slotAllPlaylistSuccess(QByteArray&)));
    connect(apiService::Instance(), SIGNAL(allPlaylistFailure()), SLOT(slotAllPlaylistFailure()));
}

PlaylistCollectionService::~PlaylistCollectionService()
{
    playlistCollection::Instance()->~PlaylistCollection();
}

void PlaylistCollectionService::loadFromService()
{
    apiService::Instance()->login();
}

void PlaylistCollectionService::updateModel()
{

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
            playlistCollection::Instance()->fromJson(edges);
        }
    }
    else {
        qWarning() << "Cant't parse playlist json data.";
    }
}

void PlaylistCollectionService::slotAllPlaylistFailure()
{

}
