#ifndef PLAYLISTCOLLECTION_H
#define PLAYLISTCOLLECTION_H

#include <QObject>

namespace Model {
class PlaylistCollection;
}

/*
 * Объект коллекции плейлистов.
 * Методы:
 *  getAllMedia - получение коллекции указателей медиа файлов
 *  из всех плейлистов.
 *  appendPlaylist - добавление плейлиста.
 *  count - количество плейлистов.
 * Свойста:
 *  collection - указатель на коллекцию плейлистов.
*/
class Playlist;
template <typename Playlist>
class QList;
class QJsonArray;
class MediaContent;

class PlaylistCollection : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistCollection(QObject *parent = 0);
    static PlaylistCollection* fromJson(QJsonArray &arr);
    QList<MediaContent *> getAllMedia();
    void appendPlaylist(Playlist *playlist);
    int count();
    ~PlaylistCollection();

private:
    QList<Playlist *> *collection;
};

#endif // PLAYLISTCOLLECTION_H
