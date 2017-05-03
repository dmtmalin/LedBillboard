#include <QVariant>
#include <QModelIndex>
#include "model/playlist.h"
#include "model/playlistcollection.h"
#include "playlisttablemodel.h"

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
    return 4;
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
            case 0:
                return QVariant(playlist->getId());
            case 1:
                return playlist->getCronCommand();
            case 2:
                return playlist->getCronDescription();
            case 3:
                return playlist->getCompany();
        }
    }
    else if (role == Qt::UserRole) {
        return QVariant::fromValue(playlist);
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
