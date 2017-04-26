#ifndef PLAYLIST_H
#define PLAYLIST_H

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
    static Playlist* fromJson(QJsonObject &obj);
    void setId(QString &id);
    void setCronCommand(QString &command);
    void setCronDescription(QString &desc);
    QString getId();
    QString getCronCommand();
    QString getCronDescription();

private:
    QString id;
    QString cronCommand;
    QString cronDescription;
    QList<MediaContent *> *mediaContent;
};

#endif // PLAYLIST_H
