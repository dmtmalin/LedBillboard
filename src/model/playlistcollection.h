#ifndef PLAYLISTCOLLECTION_H
#define PLAYLISTCOLLECTION_H

#include <QObject>
#include "singleton.h"

class Playlist;
template <typename Playlist>
class QList;
class QJsonArray;

class PlaylistCollection : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistCollection(QObject *parent = 0);
    void fromJson(QJsonArray &arr);
    ~PlaylistCollection();

private:
    QList<Playlist> *collection;
};

typedef Singleton<PlaylistCollection> playlistCollection;

#endif // PLAYLISTCOLLECTION_H
