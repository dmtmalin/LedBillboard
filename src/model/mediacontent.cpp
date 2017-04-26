#include <QString>
#include <QJsonObject>
#include "mediacontent.h"

MediaContent::MediaContent()
{
}

MediaContent *MediaContent::fromJson(QJsonObject &obj)
{
    QString id = obj["id"].toString();
    QString url = obj["url"].toString();
    MediaContent* media = new MediaContent();
    media->setId(id);
    media->setUrl(url);
    return media;
}

/*
 * SETTERS
*/

void MediaContent::setId(QString &id)
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

QString MediaContent::getId()
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
