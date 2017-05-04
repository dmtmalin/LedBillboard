#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkCookie>
#include <QSslError>
#include "model/mediacontent.h"
#include "settings.h"
#include "utils.h"
#include "apiservice.h"

const QString ApiService::LOGIN_URL = "/account/ajax_login";
const QString ApiService::GRAPH_URL = "/graphql";

ApiService::ApiService(QObject *parent) : QObject(parent)
{
    this->cookie = new MyCookieJar();
    this->manager = new QNetworkAccessManager(this);
    this->manager->setCookieJar(this->cookie);
}

void ApiService::login()
{
    QUrlQuery query;
    QString username = settings::Instance()->getValue(Settings::USERNAME);
    QString password = settings::Instance()->getValue(Settings::PASSWORD);
    query.addQueryItem("username", username);
    query.addQueryItem("password", password);
    QString host = settings::Instance()->getValue(Settings::HOST);
    QUrl url(host + ApiService::LOGIN_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData = query.toString(QUrl::FullyEncoded).toUtf8();
    QNetworkReply *reply = this->manager->post(request, postData);
    connect(reply, SIGNAL(finished()), SLOT(slotLoginFinished()));
#ifndef QT_NO_SSL
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(slotSslErrors(QList<QSslError>)));
#endif
}

void ApiService::allPlaylist(const QString &boardSlug)
{
    QUrlQuery query;
    QString graphQuery = QString("query {"
            "allPlaylist(board_Slug: \"%1\") {"
              "edges {"
                "node {"
                  "baseId,"
                  "company,"
                  "schedule { id, cron, description },"
                  "media { id, file, duration, createAt, url }}}}}").arg(boardSlug);
    query.addQueryItem("query", graphQuery);
    QString host = settings::Instance()->getValue(Settings::HOST);
    QUrl url(host + ApiService::GRAPH_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData = query.toString(QUrl::FullyEncoded).toUtf8();
    QNetworkReply *reply = this->manager->post(request, postData);
    connect(reply, SIGNAL(finished()), SLOT(slotAllPlaylistFinished()));
#ifndef QT_NO_SSL
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(slotSslErrors(QList<QSslError>)));
#endif
}

void ApiService::downloadFile(QString &url, QString &filename)
{
    QUrl _url(url);
    QNetworkRequest request(_url);
    request.setAttribute(QNetworkRequest::User, filename);
    QNetworkReply *reply = this->manager->get(request);
    connect(reply, SIGNAL(finished()), SLOT(slotDownloadFinished()));
#ifndef QT_NO_SSL
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(slotSslErrors(QList<QSslError>)));
#endif
}

MyCookieJar *ApiService::getCookie()
{
    return this->cookie;
}

/*
 * SLOTS
*/

void ApiService::slotLoginFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error() == QNetworkReply::NoError) {
        qInfo() << "Authentication success.";
        emit loginSuccess();        
    }
    else {
        qWarning() << QString("Authentication failed. %1.").arg(reply->errorString());
        emit loginFailure();        
    }    
    reply->deleteLater();
}

void ApiService::slotAllPlaylistFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        qInfo() << "Get playlist data is successful.";
        emit allPlaylistSuccess(data);        
    }
    else {
        qWarning() << QString("Get playlist data is failed. %1.").arg(reply->errorString());
        emit allPlaylistFailure();        
    }
    reply->deleteLater();
}

void ApiService::slotDownloadFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error() == QNetworkReply::NoError) {
        QUrl url = reply->url();
        QString filename = reply->request().attribute(QNetworkRequest::User).toString();
        if (Utils::saveToDisk(filename, reply)) {
            qInfo() << QString("Download of %1 succeeded (saved to %2).").arg(
                           url.toEncoded().constData(), filename);
            emit downloadFinished();
        }
    }
    else {
        qWarning() << QString("Download media is failed: %1.").arg(reply->errorString());
    }
    reply->deleteLater();
}

void ApiService::slotSslErrors(const QList<QSslError> &errors)
{
#ifndef QT_NO_SSL
    foreach (const QSslError &error, errors)
        qWarning() << QString("SSL Error: %1.").arg(error.errorString());
#else
    Q_UNUSED(sslErrors);
#endif
}

ApiService::~ApiService()
{
    delete this->cookie;
    delete this->manager;
}

bool MyCookieJar::isEmpty()
{
    return (allCookies().count() > 0) ? false : true;
}

void MyCookieJar::clear()
{
    QList<QNetworkCookie> cookies = allCookies();
    foreach (QNetworkCookie cookie, cookies) {
        deleteCookie(cookie);
    }
}
