#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include "model/playlist.h"
#include "playlistcollection.h"

PlaylistCollection::PlaylistCollection(QObject *parent) : QObject(parent)
{
    this->collection = new QList<Playlist>();
}

void PlaylistCollection::fromJson(QJsonArray &arr)
{
    foreach (const QJsonValue &item, arr) {
        QJsonObject node = item.toObject()
                ["node"].toObject();
        Playlist playlist = Playlist::fromJson(node);
        collection->append(playlist);
    }
}

PlaylistCollection::~PlaylistCollection()
{
    delete this->collection;
}
