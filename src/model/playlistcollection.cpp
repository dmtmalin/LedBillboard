#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include "model/playlist.h"
#include "playlistcollection.h"

PlaylistCollection::PlaylistCollection(QObject *parent) : QObject(parent)
{
    this->collection = new QList<Playlist *>();
}

void PlaylistCollection::fromJson(QJsonArray &arr)
{
    foreach (const QJsonValue &item, arr) {
        QJsonObject node = item.toObject()
                ["node"].toObject();
        Playlist *playlist = Playlist::fromJson(node);
        collection->append(playlist);
    }
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

int PlaylistCollection::count()
{
    return this->collection->count();
}

PlaylistCollection::~PlaylistCollection()
{
    qDeleteAll(this->collection->begin(), this->collection->end());
    delete this->collection;
}
