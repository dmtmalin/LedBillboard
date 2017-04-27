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
class MyCookiejar : public QNetworkCookieJar
{
public:
    bool isEmpty();
    void clear();
};


/*
 * Класс-сервис для работы с API.
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

private:
    QNetworkAccessManager *manager;
    MyCookiejar *cookie;

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
