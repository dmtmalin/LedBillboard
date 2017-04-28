#ifndef APISERVICE_H
#define APISERVICE_H

#include <QObject>
#include <QNetworkCookieJar>
#include "singleton.h"

extern const char* LOGIN_URL;
extern const char* GRAPH_URL;

namespace Service {
class ApiService;
}

class QString;
class QByteArray;
class QNetworkAccessManager;
class QNetworkReply;
class QSslError;
class MediaContent;

/**
 * @brief The MyCookieJar class класс для работы с cookie.
 */
class MyCookieJar : public QNetworkCookieJar
{
public:
    bool isEmpty();
    void clear();
};

class ApiService : public QObject
{
    Q_OBJECT
public:
    explicit ApiService(QObject *parent = 0);
    ~ApiService();
    /**
     * @brief login авторизация на сервисе. Используется механиз сессий.
     * Id сессии сохранется в cookies (MyCookieJar).
     */
    void login();
    /**
     * @brief allPlaylist получение коллекции плейлистов.
     * @param boardSlug уникальное имя билборда.
     */
    void allPlaylist(const QString &boardSlug);
    /**
     * @brief downloadFile скачивание файла.
     * @param url адрес файла.
     * @param filename полное имя файла для сохранения.
     */
    void downloadFile(QString &url, QString &filename);
    /**
     * @brief getCookie получение указателя на cookie.
     * @return указатель на объект.
     */
    MyCookieJar* getCookie();

private:
    QNetworkAccessManager *manager;
    MyCookieJar *cookie;

private slots:
    /**
     * @brief slotLoginFinished обработка ответа аутентификации.
     */
    void slotLoginFinished();
    /**
     * @brief slotAllPlaylistFinished обработка ответа на получение
     * коллекции плейлистов.
     */
    void slotAllPlaylistFinished();
    /**
     * @brief slotDownloadFinished обработка ответа на скачивание файла
     * (получение медиа).
     */
    void slotDownloadFinished();
    /**
     * @brief slotSslErrors обработка ошибок SSL. Ззапись в лог.
     * @param errors
     */
    void slotSslErrors(const QList<QSslError> &errors);

signals:
    /**
     * @brief loginSuccess сигнал успешного логина.
     */
    void loginSuccess();
    /**
     * @brief loginFailure сигнал неудачной аутентификации
     * (неавторизован/сетевая ошибка).
     */
    void loginFailure();
    /**
     * @brief allPlaylistFailure сигнал неудачного получения коллекции
     * плейлистов (доступ запрещен/сетевая ошибка).
     *
     */
    void allPlaylistFailure();
    /**
     * @brief allPlaylistSuccess сигнал успешного получения
     * коллекции плейлистов.
     */
    void allPlaylistSuccess(QByteArray&);
    /**
     * @brief downloadFinished сигнал завершения скачивания файла.
     * Сохранение в файл.
     */
    void downloadFinished();
};

typedef Singleton<ApiService> apiService;

#endif // APISERVICE_H
