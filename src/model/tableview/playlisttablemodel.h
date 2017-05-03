#ifndef PLAYLISTTABLEMODEL_H
#define PLAYLISTTABLEMODEL_H

#include <QAbstractTableModel>

class QVariant;
class QModelIndex;
class PlaylistCollection;

class PlaylistTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PlaylistTableModel(PlaylistCollection *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private:
    PlaylistCollection *collection;
private slots:
    void slotBegunUpdate();
    void slotFinishedUpdate();
};

#endif // PLAYLISTTABLEMODEL_H
