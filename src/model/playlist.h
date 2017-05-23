#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>

namespace Model {
class Playlist;
}

class MediaContent;
class QString;
template <typename MediaContent>
class QList;
class QJsonObject;
template <typename MediaContent>
class QMutableListIterator;

class Playlist : public QObject
{
    Q_OBJECT
public:
    explicit Playlist(QObject *parent = 0);
    /**
     * @brief fromJson создание объекта из JSON.
     * @param obj объект JSON.
     * @return указатель на объект.
     */
    static Playlist* fromJson(QJsonObject &obj, QObject *parent = 0);
    void setId(int &id);
    void setCronCommand(QString &command);
    void setCronDescription(QString &desc);
    void setCompany(QString &name);
    int getId();
    QString getCronCommand();
    QString getCronDescription();
    QString getCompany();
    QList<MediaContent *> *getMediaContent();
    MediaContent *getMedia(int index);
    MediaContent *nextMedia();
    void addMedia(MediaContent* media);
    ~Playlist();

private:
    /**
     * @brief id внутренний id.
     */
    int id;
    /**
     * @brief cronCommand крон комманда.
     */
    QString cronCommand;
    /**
     * @brief cronDescription описание крон комманды.
     */
    QString cronDescription;
    /**
     * @brief company наименование компании.
     */
    QString company;
    /**
     * @brief mediaContent указатель на коллекцию медиа файлов.
     */
    QList<MediaContent *> *mediaContent;
    QMutableListIterator<MediaContent *> *iMediaContent;
};

#endif // PLAYLIST_H
