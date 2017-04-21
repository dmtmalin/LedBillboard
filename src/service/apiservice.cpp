#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkCookieJar>
#include "apiservice.h"
#include "settings.h"

const char* LOGIN_URL =  "/account/ajax_login";

ApiService::ApiService(QObject *parent) : QObject(parent)
{
    this->cookie = new QNetworkCookieJar();
    this->manager = new QNetworkAccessManager(this);
    this->manager->setCookieJar(cookie);
}

void ApiService::login()
{
    QUrlQuery query;
    QString username = Settings::value(Settings::USERNAME);
    QString password = Settings::value(Settings::PASSWORD);
    query.addQueryItem("username", username);
    query.addQueryItem("password", password);
    QString host = Settings::value(Settings::HOST);
    QUrl url(host + LOGIN_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData = query.toString(QUrl::FullyEncoded).toUtf8();
    QNetworkReply *reply = this->manager->post(request, postData);

    connect(reply, SIGNAL(finished()), SLOT(slotLoginFinished()));
}

void ApiService::slotLoginFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error() == QNetworkReply::NoError ) {
        qInfo() << "Is loggin";
    }

    reply->deleteLater();
}

ApiService::~ApiService()
{
    delete this->cookie;
    delete this->manager;
}
