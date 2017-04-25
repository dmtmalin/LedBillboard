#ifndef APISERVICE_H
#define APISERVICE_H

#include <QObject>
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
class QNetworkCookieJar;

class ApiService : public QObject
{
    Q_OBJECT
public:
    explicit ApiService(QObject *parent = 0);
    ~ApiService();
    void login();
    void allPlaylist(QString &boardSlug);

private:
    QNetworkAccessManager *manager;
    QNetworkCookieJar *cookie;

private slots:
    void slotLoginFinished();
    void slotAllPlaylistFinished();

signals:
    void loginSuccess();
    void loginFailure();
    void allPlaylistFailure();
    void allPlaylistSuccess(QByteArray&);
};

typedef Singleton<ApiService> apiService;

#endif // APISERVICE_H
