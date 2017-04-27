#ifndef PLAYLIST_H
#define PLAYLIST_H

namespace Model {
class Playlist;
}

class MediaContent;
class QString;
template <typename MediaContent>
class QList;
class QJsonObject;

/*
 * Объект плейлиста.
 * Методы:
 *  fromJson - создание объекта из JSON.
 *  getMediaContent - получение коллекции указателей на объекты медиа.
 * Свойства:
 *  id - внутренний id.
 *  cronCommand - крон комманда.
 *  cronDescription - описание крон комманды.
 *  mediaContent - указатель на коллекцию медиа файлов.
*/
class Playlist
{
public:
    Playlist();
    ~Playlist();
    static Playlist* fromJson(QJsonObject &obj);
    void setId(QString &id);
    void setCronCommand(QString &command);
    void setCronDescription(QString &desc);
    QString getId();
    QString getCronCommand();
    QString getCronDescription();
    QList<MediaContent *> *getMediaContent();

private:
    QString id;
    QString cronCommand;
    QString cronDescription;
    QList<MediaContent *> *mediaContent;
};

#endif // PLAYLIST_H
