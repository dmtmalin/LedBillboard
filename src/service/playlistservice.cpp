#include <QtDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "model/playlist.h"
#include "service/apiservice.h"
#include "settings.h"
#include "playlistservice.h"


PlaylistService::PlaylistService(QObject *parent) : QObject(parent)
{
    connect(apiService::Instance(), SIGNAL(loginSuccess()), SLOT(slotLoginSuccess()));
    connect(apiService::Instance(), SIGNAL(loginFailure()), SLOT(slotLoginFailure()));
    connect(apiService::Instance(), SIGNAL(allPlaylistSuccess(QByteArray&)),
            SLOT(slotAllPlaylistSuccess(QByteArray&)));
    connect(apiService::Instance(), SIGNAL(allPlaylistFailure()), SLOT(slotAllPlaylistFailure()));
}

PlaylistService::~PlaylistService()
{

}

void PlaylistService::initializeModel()
{
    apiService::Instance()->login();
}

void PlaylistService::updateModel()
{

}

/*
 * SLOTS
*/

void PlaylistService::slotLoginSuccess()
{
    QString board = settings::Instance()->getValue(Settings::BOARD);
    apiService::Instance()->allPlaylist(board);
}

void PlaylistService::slotLoginFailure()
{

}

void PlaylistService::slotAllPlaylistSuccess(QByteArray &arr)
{
    QJsonDocument doc = QJsonDocument::fromJson(arr);
    Playlist playlist = Playlist::fromJson(doc);
}

void PlaylistService::slotAllPlaylistFailure()
{

}
