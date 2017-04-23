#ifndef APISERVICE_H
#define APISERVICE_H

#include <QObject>

extern const char* LOGIN_URL;

namespace Service {
class ApiService;
}

class QString;
class QNetworkAccessManager;
class QNetworkReply;
class QNetworkCookieJar;

class ApiService : public QObject
{
    Q_OBJECT
public:
    static ApiService& Instance() {
        static ApiService theSingleInstance;
        return theSingleInstance;
    }
    ~ApiService();
    void login();

private:
    explicit ApiService(QObject *parent = 0);    

    QNetworkAccessManager *manager;
    QNetworkCookieJar *cookie;

private slots:
    void slotLoginFinished();

};

#endif // APISERVICE_H
