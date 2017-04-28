#ifndef PLAYLISTCOLLECTIONSERVICE_H
#define PLAYLISTCOLLECTIONSERVICE_H

#include <QObject>
#include "singleton.h"

namespace Service {
class PlaylistCollectionService;
}

class QByteArray;
class PlaylistCollection;

class PlaylistCollectionService : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistCollectionService(QObject *parent = 0);
    ~PlaylistCollectionService();
    /**
     * @brief loadFromService синхронизация коллекции плейлистов с сервиса.
     * Если залогинен, то получаем коллекцию (ApiService::allPlaylist), в противном
     * случае сначала проходим аутентификацию (ApiService::login).
     */
    void loadFromService();
    /**
     * @brief DownloadMediaFiles скачивание медиа файлов.
     */
    void DownloadMediaFiles();

private:
    int downloadCounter;
    PlaylistCollection *playlistCollection;

private slots:
    /**
     * @brief slotLoginSuccess обработка успешной аутентификации. После нее получаем
     * коллекцию плейлистов (ApiService::allPlaylist).
     */
    void slotLoginSuccess();
    /**
     * @brief slotLoginFailure обработка неудачной аутентификации.
     * Повторяем через Settings::RETRY.
     */
    void slotLoginFailure();
    /**
     * @brief slotAllPlaylistSuccess обработка успешного получения коллекции плейлистов.
     * @param arr ответ от сервиса в bytes.
     */
    void slotAllPlaylistSuccess(QByteArray &arr);
    /**
     * @brief slotAllPlaylistFailure обработка неудачного получения коллекции плейлистов.
     * Повторяем loadFromService через Setings::RETRY.
     */
    void slotAllPlaylistFailure();
    /**
     * @brief slotDownloadFinished обработка сигнала скачивания файла. Считаем сколько
     * осталось до скачивания всех файлов через downloadCounter.
     */
    void slotDownloadFinished();    
signals:
    /**
     * @brief successLoadFromService сигнал успешной синхронизации плейлистов с сервиса.
     * После него подразумевается запуск синхронизации медиа (DownloadMediaFiles).
     */
    void successLoadFromService();
    /**
     * @brief successDownloadMediaFiles сигнал успешной синхронизации медиа.
     */
    void successDownloadMediaFiles();
};

typedef Singleton<PlaylistCollectionService> playlistCollectionService;

#endif // PLAYLISTCOLLECTIONSERVICE_H
