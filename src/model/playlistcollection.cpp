#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include "model/playlist.h"
#include "playlistcollection.h"

PlaylistCollection::PlaylistCollection(QObject *parent) : QObject(parent)
{
    this->collection = new QList<Playlist *>();
}

PlaylistCollection *PlaylistCollection::fromJson(QJsonArray &arr)
{
    PlaylistCollection *playlistCollection = new PlaylistCollection();
    foreach (const QJsonValue &item, arr) {
        QJsonObject node = item.toObject()
                ["node"].toObject();
        Playlist *playlist = Playlist::fromJson(node);
        playlistCollection->appendPlaylist(playlist);
    }
    return playlistCollection;
}

QList<MediaContent *> PlaylistCollection::getAllMedia()
{
    QList<MediaContent *> allMedia;
    foreach (Playlist *playlist, *this->collection) {
        QList<MediaContent *> *mediaContent = playlist->getMediaContent();
        foreach (MediaContent *media, *mediaContent) {
            allMedia.append(media);
        }
    }
    return allMedia;
}

void PlaylistCollection::appendPlaylist(Playlist *playlist)
{
    this->collection->append(playlist);
}

int PlaylistCollection::count()
{
    return this->collection->count();
}

PlaylistCollection::~PlaylistCollection()
{
    qDeleteAll(this->collection->begin(), this->collection->end());
    delete this->collection;
}
