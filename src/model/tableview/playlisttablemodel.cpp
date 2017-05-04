#include <QVariant>
#include <QModelIndex>
#include "model/playlist.h"
#include "model/playlistcollection.h"
#include "playlisttablemodel.h"

const unsigned short PlaylistTableModel::COLUMNS = 4;
const unsigned short PlaylistTableModel::ID = 0;
const unsigned short PlaylistTableModel::CRON = 1;
const unsigned short PlaylistTableModel::CRON_DESC = 2;
const unsigned short PlaylistTableModel::COMPANY = 3;

PlaylistTableModel::PlaylistTableModel(PlaylistCollection *parent)
    :QAbstractTableModel(parent)
{
    this->collection = parent;
    connect(this->collection, SIGNAL(begunUpdate()), SLOT(slotBegunUpdate()));
    connect(this->collection, SIGNAL(finishedUpdate()), SLOT(slotFinishedUpdate()));
}

int PlaylistTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->collection->count();
}

int PlaylistTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return PlaylistTableModel::COLUMNS;
}

QVariant PlaylistTableModel::data(const QModelIndex &index, int role) const
{    
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= this->collection->count() || row < 0)
        return QVariant();

    Playlist *playlist = this->collection->getPlaylist(row);

    if (role == Qt::DisplayRole) {
        switch (col) {
            case PlaylistTableModel::ID:
                return QVariant(playlist->getId());
            case PlaylistTableModel::CRON:
                return playlist->getCronCommand();
            case PlaylistTableModel::CRON_DESC:
                return playlist->getCronDescription();
            case PlaylistTableModel::COMPANY:
                return playlist->getCompany();
        }
    }
    else if (role == Qt::UserRole) {
        return QVariant::fromValue(playlist);
    }
    return QVariant();
}

QVariant PlaylistTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

     if (orientation == Qt::Horizontal) {
         switch (section) {
            case PlaylistTableModel::ID:
                return tr("ID");
            case PlaylistTableModel::CRON:
                return tr("Команда cron");
            case PlaylistTableModel::CRON_DESC:
                return tr("Описание cron");
            case PlaylistTableModel::COMPANY:
                return tr("Компания");
            default:
                return QVariant();
         }
     }
     return QVariant();
}

void PlaylistTableModel::slotBegunUpdate()
{
    beginResetModel();
}

void PlaylistTableModel::slotFinishedUpdate()
{
    endResetModel();
}
