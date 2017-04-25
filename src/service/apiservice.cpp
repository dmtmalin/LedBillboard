#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkCookieJar>
#include "apiservice.h"
#include "settings.h"

const char* LOGIN_URL = "/account/ajax_login";
const char* GRAPH_URL = "/graphql";

ApiService::ApiService(QObject *parent) : QObject(parent)
{
    this->cookie = new QNetworkCookieJar();
    this->manager = new QNetworkAccessManager(this);
    this->manager->setCookieJar(cookie);
}

void ApiService::login()
{
    QUrlQuery query;
    QString username = settings::Instance()->getValue(Settings::USERNAME);
    QString password = settings::Instance()->getValue(Settings::PASSWORD);
    query.addQueryItem("username", username);
    query.addQueryItem("password", password);
    QString host = settings::Instance()->getValue(Settings::HOST);
    QUrl url(host + LOGIN_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData = query.toString(QUrl::FullyEncoded).toUtf8();
    QNetworkReply *reply = this->manager->post(request, postData);

    connect(reply, SIGNAL(finished()), SLOT(slotLoginFinished()));
}

void ApiService::allPlaylist(QString &boardSlug)
{
    QUrlQuery query;
    QString graphQuery = QString("query {"
            "allPlaylist(board_Slug: \"%1\") {"
              "edges {"
                "node {"
                  "id,"
                  "schedule { id, cron, description },"
                  "media { id, file, duration, createAt, url }}}}}").arg(boardSlug);
    query.addQueryItem("query", graphQuery);
    QString host = settings::Instance()->getValue(Settings::HOST);
    QUrl url(host + GRAPH_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData = query.toString(QUrl::FullyEncoded).toUtf8();
    QNetworkReply *reply = this->manager->post(request, postData);

    connect(reply, SIGNAL(finished()), SLOT(slotAllPlaylistFinished()));
}

void ApiService::slotLoginFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error() == QNetworkReply::NoError) {
        emit loginSuccess();
        qInfo() << "Authentication success.";
    }
    else {
        emit loginFailure();
        qWarning() << QString("Authentication failed. %1.").arg(reply->errorString());
    }
    reply->deleteLater();
}

void ApiService::slotAllPlaylistFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        emit allPlaylistSuccess(data);
        qInfo() << "Get playlist data is successful.";
    }
    else {
        emit allPlaylistFailure();
        qWarning() << QString("Get playlist data is failed. %1.").arg(reply->errorString());
    }
    reply->deleteLater();
}

ApiService::~ApiService()
{
    delete this->cookie;
    delete this->manager;
}
