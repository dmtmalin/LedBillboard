#ifndef PLAYLISTCOLLECTIONSERVICE_H
#define PLAYLISTCOLLECTIONSERVICE_H

#include <QObject>
#include "singleton.h"

namespace Service {
class PlaylistCollectionService;
}

class QByteArray;
class PlaylistCollection;

/*
 * Одиночка управления коллекцией плейлистов.
 * Методы:
 *  loadFromService - синхронизация коллекции плейлистов с сервиса.
 *  Если залогинен, то получаем коллекцию (ApiService::allPlaylist), в противном
 *  случае сначала проходим аутентификацию (ApiService::login).
 *  DownloadMediaFiles - скачивание медиа файлов.
 * Слоты:
 *  slotLoginSuccess - обработка успешной аутентификации. После нее получаем
 *  коллекцию плейлистов (ApiService::allPlaylist).
 *  slotLoginFailure - обработка неудачной аутентификации. Повторяем через Settings::RETRY.
 *  slotAllPlaylistSuccess - обработка успешного получения коллекции плейлистов.
 *  Заполняем playlistCollection.
 *  slotAllPlaylistFailure - обработка неудачного получения коллекции плейлистов. Повторяем
 *  loadFromService через Setings::RETRY.
 * Сигналы:
 *  successLoadFromService - сигнал успешной синхронизации плейлистов с сервиса.
 *  После него подразумевается запуск синхронизации медиа (DownloadMediaFiles).
 *  successDownloadMediaFiles - сигнал успешной синхронизации медиа.
*/
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
    PlaylistCollection *playlistCollection;

private slots:
    void slotLoginSuccess();
    void slotLoginFailure();
    void slotAllPlaylistSuccess(QByteArray &arr);
    void slotAllPlaylistFailure();
    void slotDownloadFinished();    
signals:
    void successLoadFromService();
    void successDownloadMediaFiles();
};

typedef Singleton<PlaylistCollectionService> playlistCollectionService;

#endif // PLAYLISTCOLLECTIONSERVICE_H
