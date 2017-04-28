#ifndef PLAYLISTCOLLECTION_H
#define PLAYLISTCOLLECTION_H

#include <QObject>

namespace Model {
class PlaylistCollection;
}

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
    /**
     * @brief fromJson создание объекта из JSON.
     * @param arr масссив JSON.
     * @return указатель на объект.
     */
    static PlaylistCollection* fromJson(QJsonArray &arr);
    QList<MediaContent *> getAllMedia();
    /**
     * @brief appendPlaylist добавление плейлиста в коллекцию.
     * @param playlist указатель на объект плейлиста.
     */
    void appendPlaylist(Playlist *playlist);
    /**
     * @brief count количество плейлистов в коллекции.
     * @return количество.
     */
    int count();
    ~PlaylistCollection();

private:
    /**
     * @brief collection коллекция плейлистов.
     */
    QList<Playlist *> *collection;
};

#endif // PLAYLISTCOLLECTION_H
