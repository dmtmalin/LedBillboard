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

Playlist Playlist::fromJson(QJsonDocument &doc)
{
    Playlist playlist;
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        QJsonArray edges = obj.take("edges").toArray();
        if (edges.isEmpty()) {
            qInfo() << "Playlist data is empty.";
        }
        else {

        }
    }
    else {
        qWarning() << "Cant't parse playlist data.";
    }

    return playlist;
}
