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

class Playlist
{
public:
    Playlist();
    ~Playlist();
    /**
     * @brief fromJson создание объекта из JSON.
     * @param obj объект JSON.
     * @return указатель на объект.
     */
    static Playlist* fromJson(QJsonObject &obj);
    void setId(QString &id);
    void setCronCommand(QString &command);
    void setCronDescription(QString &desc);
    QString getId();
    QString getCronCommand();
    QString getCronDescription();
    QList<MediaContent *> *getMediaContent();

private:
    /**
     * @brief id внутренний id.
     */
    QString id;
    /**
     * @brief cronCommand крон комманда.
     */
    QString cronCommand;
    /**
     * @brief cronDescription описание крон комманды.
     */
    QString cronDescription;
    /**
     * @brief mediaContent указатель на коллекцию медиа файлов.
     */
    QList<MediaContent *> *mediaContent;
};

#endif // PLAYLIST_H
