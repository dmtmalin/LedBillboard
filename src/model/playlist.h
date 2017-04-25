#ifndef PLAYLIST_H
#define PLAYLIST_H

class MediaContent;
class QString;
template <typename MediaContent>
class QList;
class QJsonDocument;

class Playlist
{
public:
    Playlist();
    ~Playlist();
    static Playlist fromJson(QJsonDocument &doc);

private:
    QString id;
    QString cronCommand;
    QString cronDescription;
    QList<MediaContent> *mediaContent;
};

#endif // PLAYLIST_H
