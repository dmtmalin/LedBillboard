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
class QStringListModel;
class MediaContent;

class PlaylistCollection : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistCollection(QObject *parent = 0);
    /**
     * @brief updateFromJson обновление объекта через объект JSON
     * @param arr масссив JSON
     */
    void updateFromJson(QJsonArray &arr);
    /**
     * @brief getAllMedia получение медиа плейлистов.
     * @return массив указателей на медиа.
     */
    QList<MediaContent *> getAllMedia();
    /**
     * @brief count количество плейлистов в коллекции.
     * @return количество.
     */
    int count();
    /**
     * @brief getPlaylist возвращает плейлист по индексу.
     * @param index индекс.
     * @return указатель на объект.
     */
    Playlist *getPlaylist(const int index);
    /**
     * @brief clear очистить плейлисты в коллекции.
     */
    void clear();
    ~PlaylistCollection();

private:
    /**
     * @brief collection коллекция плейлистов.
     */
    QList<Playlist *> *collection;
signals:
    /**
     * @brief beginedUpdate сигнал о начале обновления коллекции.
     */
    void begunUpdate();
    /**
     * @brief finishedUpdate сигнал о завершении обновления коллекции.
     */
    void finishedUpdate();
};

#endif // PLAYLISTCOLLECTION_H
