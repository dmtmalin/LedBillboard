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

/*
 * Класс для работы с cookies.
*/
class MyCookieJar : public QNetworkCookieJar
{
public:
    bool isEmpty();
    void clear();
};

/*
 * Одиночка для работы с API.
 * Методы:
 *  login - авторизация на сервисе. Используется механиз сессий. Id сессии
 *  сохранется в cookies (MyCookieJar).
 *  allPlaylist - получение коллекции плейлистов.
 *  downloadFile - скачивание файла.
 * Слоты:
 *  slotLoginFinished - обработка ответа аутентификации.
 *  slotAllPlaylistFinished - обработка ответа на получение коллекции плейлистов.
 *  slotDownloadFinished - обработка ответа на скачивание файла (получение медии).
 *  slotSslErrors - обработка ошибок SSL (запись в лог).
 * Сигналы:
 *  loginSuccess - сигнал успешного логина.
 *  loginFailure - сигнал неудачной аутентификации (неавторизован/сетевая ошибка).
 *  allPlaylistFailure - сигнал неудачного получения коллекции плейлистов (доступ
 *  запрещен/сетевая ошибка).
 *  allPlaylistSuccess - сигнал успешного получения коллекции плейлистов.
 *  downloadFinished - сигнал завершения скачивания файла.
*/
class ApiService : public QObject
{
    Q_OBJECT
public:
    explicit ApiService(QObject *parent = 0);
    ~ApiService();
    void login();
    void allPlaylist(const QString &boardSlug);
    void downloadFile(QString &url, QString &filename);
    MyCookieJar* getCookie();

private:
    QNetworkAccessManager *manager;
    MyCookieJar *cookie;

private slots:
    void slotLoginFinished();
    void slotAllPlaylistFinished();
    void slotDownloadFinished();
    void slotSslErrors(const QList<QSslError> &errors);

signals:
    void loginSuccess();
    void loginFailure();
    void allPlaylistFailure();
    void allPlaylistSuccess(QByteArray&);
    void downloadFinished();
};

typedef Singleton<ApiService> apiService;

#endif // APISERVICE_H
