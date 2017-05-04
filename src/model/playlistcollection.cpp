#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringListModel>
#include "model/playlist.h"
#include "playlistcollection.h"

PlaylistCollection::PlaylistCollection(QObject *parent) : QObject(parent)
{
    this->collection = new QList<Playlist *>();
}

void PlaylistCollection::updateFromJson(QJsonArray &arr)
{    
    emit begunUpdate();
    clear();
    for(int i = 0; i < arr.size(); i++) {
        QJsonObject node = arr[i].toObject()
                ["node"].toObject();
        Playlist *playlist = Playlist::fromJson(node, this);
        this->collection->append(playlist);
    }
    emit finishedUpdate();
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

Playlist *PlaylistCollection::getPlaylist(const int index)
{
    return this->collection->at(index);
}

void PlaylistCollection::clear()
{
    qDeleteAll(this->collection->begin(), this->collection->end());
}

PlaylistCollection::~PlaylistCollection()
{
    clear();
    delete this->collection;
}
