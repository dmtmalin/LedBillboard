#ifndef MEDIATABLEMODEL_H
#define MEDIATABLEMODEL_H

#include <QAbstractTableModel>

class QVariant;
class QModelIndex;
class Playlist;

class MediaTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    MediaTableModel(Playlist *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private:
    Playlist *playlist;
};

#endif // MEDIATABLEMODEL_H
