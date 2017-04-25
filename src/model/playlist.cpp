#include <QDebug>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "model/mediacontent.h"
#include "playlist.h"

Playlist::Playlist()
{
    this->mediaContent = new QList<MediaContent>();
}

Playlist::~Playlist()
{    
    delete this->mediaContent;
}

Playlist Playlist::fromJson(QJsonObject &obj)
{
    QString id = obj["id"].toString();
    QString command = obj["schedule"].toObject()
            ["cron"].toString();
    QString description = obj["schedule"].toObject()
            ["description"].toString();
    Playlist playlist;
    playlist.setId(id);
    playlist.setCronCommand(command);
    playlist.setCronDescription(description);
    QJsonArray mediaArr = obj["media"].toArray();
    if (mediaArr.isEmpty()) {
        qWarning() << QString("Playlist %1 not have media item.").arg(id);
    }
    else {
        foreach (const QJsonValue &item, mediaArr) {
            QJsonObject obj = item.toObject();
            MediaContent media = MediaContent::fromJson(obj);
            playlist.mediaContent->append(media);
        }
    }
    return playlist;
}

/*
 * SETTERS
*/

void Playlist::setId(QString &id)
{
    this->id = id;
}

void Playlist::setCronCommand(QString &command)
{
    this->cronCommand = command;
}

void Playlist::setCronDescription(QString &desc)
{
    this->cronDescription = desc;
}

/*
 * GETTERS
*/

QString Playlist::getId()
{
    return this->id;
}

QString Playlist::getCronCommand()
{
    return this->cronCommand;
}

QString Playlist::getCronDescription()
{
    return this->cronDescription;
}
