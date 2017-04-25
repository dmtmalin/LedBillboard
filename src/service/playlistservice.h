#ifndef PLAYLISTSERVICE_H
#define PLAYLISTSERVICE_H

#include <QObject>
#include "singleton.h"

class QByteArray;

class PlaylistService : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistService(QObject *parent = 0);
    ~PlaylistService();
    void initializeModel();
    void updateModel();

private slots:
    void slotLoginSuccess();
    void slotLoginFailure();
    void slotAllPlaylistSuccess(QByteArray &arr);
    void slotAllPlaylistFailure();
};

typedef Singleton<PlaylistService> playlistService;

#endif // PLAYLISTSERVICE_H
