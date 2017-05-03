#include <QString>
#include <QVariant>
#include <QModelIndex>
#include "model/playlist.h"
#include "model/mediacontent.h"
#include "mediatablemodel.h"

MediaTableModel::MediaTableModel(Playlist *parent)
    :QAbstractTableModel(parent)
{
    this->playlist = parent;
}

int MediaTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->playlist->getMediaContent()->count();
}

int MediaTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant MediaTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= this->playlist->getMediaContent()->count() || row < 0)
        return QVariant();

    MediaContent *media = this->playlist->getMedia(row);

    if (role == Qt::DisplayRole) {
        switch (col) {
            case 0:
                return QVariant(media->getId());
            case 1:
                return media->getUrl();
            case 2:
                return media->getFileName();
        }
    }
    return QVariant();
}
