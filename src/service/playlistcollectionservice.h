#ifndef PLAYLISTCOLLECTIONSERVICE_H
#define PLAYLISTCOLLECTIONSERVICE_H

#include <QObject>
#include "singleton.h"

namespace Service {
class PlaylistCollectionService;
}

class QByteArray;

class PlaylistCollectionService : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistCollectionService(QObject *parent = 0);
    ~PlaylistCollectionService();
    void loadFromService();
    void DownloadMediaFiles();

private:
    int downloadCounter;

private slots:
    void slotLoginSuccess();
    void slotLoginFailure();
    void slotAllPlaylistSuccess(QByteArray &arr);
    void slotAllPlaylistFailure();
    void slotDownloadFinished();
signals:
    void successAllPlaylist();
    void successDownloadMediaFiles();
};

typedef Singleton<PlaylistCollectionService> playlistCollectionService;

#endif // PLAYLISTCOLLECTIONSERVICE_H
