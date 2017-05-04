#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QUrl>
#include "utils.h"
#include "mediacontent.h"

MediaContent::MediaContent(QObject *parent) : QObject(parent)
{
}

MediaContent *MediaContent::fromJson(QJsonObject &obj, QObject *parent)
{
    int id = obj["id"].toInt();
    QString url = obj["url"].toString();
    QString filename = Utils::getFileName(QUrl(url), "media");
    MediaContent* media = new MediaContent(parent);
    media->setId(id);
    media->setUrl(url);
    media->setFileName(filename);
    return media;
}

/*
 * SETTERS
*/

void MediaContent::setId(int &id)
{
    this->id = id;
}

void MediaContent::setUrl(QString &url)
{
    this->url = url;
}

void MediaContent::setFileName(QString &fileName)
{
    this->fileName = fileName;
}

/*
 * GETTERS
*/

int MediaContent::getId()
{
    return this->id;
}

QString MediaContent::getUrl()
{
    return this->url;
}

QString MediaContent::getFileName()
{
    return this->fileName;
}
