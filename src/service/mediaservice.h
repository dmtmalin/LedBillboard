#ifndef MEDIASERVICE_H
#define MEDIASERVICE_H

#include <QObject>
#include "singleton.h"

class MediaService : public QObject
{
    Q_OBJECT
public:
    explicit MediaService(QObject *parent = 0);
    /**
     * @brief DownloadMediaFiles скачивание медиа файлов.
     */
    void DownloadMediaFiles();

private:
    int downloadCounter;

signals:
    /**
     * @brief successDownloadMediaFiles сигнал синхронизации медиа.
     */
    void finishedDownloadMediaFiles();

private slots:
    /**
     * @brief slotDownloadFinished обработка сигнала скачивания файла. Считаем сколько
     * осталось до скачивания всех файлов через downloadCounter.
     */
    void slotDownloadFinished();
};

typedef Singleton<MediaService> mediaService;

#endif // MEDIASERVICE_H
