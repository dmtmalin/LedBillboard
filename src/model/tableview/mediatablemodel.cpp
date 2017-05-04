#include <QFile>
#include <QString>
#include <QVariant>
#include <QModelIndex>
#include "model/playlist.h"
#include "model/mediacontent.h"
#include "mediatablemodel.h"

const unsigned short MediaTableModel::COLUMNS = 4;
const unsigned short MediaTableModel::ID = 0;
const unsigned short MediaTableModel::URL = 1;
const unsigned short MediaTableModel::FILE = 2;
const unsigned short MediaTableModel::EXISTS =3;

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
    return MediaTableModel::COLUMNS;
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
            case MediaTableModel::ID:
                return QVariant(media->getId());
            case MediaTableModel::URL:
                return media->getUrl();
            case MediaTableModel::FILE:
                return media->getFileName();
            case MediaTableModel::EXISTS:
                QString filename = media->getFileName();
                return QFile::exists(filename) ? tr("Да") : tr("Нет");
        }
    }
    return QVariant();
}

QVariant MediaTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

     if (orientation == Qt::Horizontal) {
         switch (section) {
            case MediaTableModel::ID:
                return tr("ID");
            case MediaTableModel::URL:
                return tr("URL");
            case MediaTableModel::FILE:
                return tr("Путь к файлу");
            case MediaTableModel::EXISTS:
                return tr("На диске");
            default:
                return QVariant();
         }
     }
     return QVariant();
}
