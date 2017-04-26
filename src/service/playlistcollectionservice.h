#ifndef PLAYLISTCOLLECTIONSERVICE_H
#define PLAYLISTCOLLECTIONSERVICE_H

#include <QObject>
#include "singleton.h"

class QByteArray;

class PlaylistCollectionService : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistCollectionService(QObject *parent = 0);
    ~PlaylistCollectionService();
    void loadFromService();
    void updateModel();

private slots:
    void slotLoginSuccess();
    void slotLoginFailure();
    void slotAllPlaylistSuccess(QByteArray &arr);
    void slotAllPlaylistFailure();
};

typedef Singleton<PlaylistCollectionService> playlistCollectionService;

#endif // PLAYLISTCOLLECTIONSERVICE_H
