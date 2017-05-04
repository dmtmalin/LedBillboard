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
    static const unsigned short COLUMNS;
    static const unsigned short ID;
    static const unsigned short CRON;
    static const unsigned short CRON_DESC;
    static const unsigned short COMPANY;
    PlaylistTableModel(PlaylistCollection *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    PlaylistCollection *collection;
private slots:
    void slotBegunUpdate();
    void slotFinishedUpdate();
};

#endif // PLAYLISTTABLEMODEL_H
