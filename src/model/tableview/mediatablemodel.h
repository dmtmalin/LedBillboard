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
    static const unsigned short COLUMNS;
    static const unsigned short ID;
    static const unsigned short URL;
    static const unsigned short FILE;
    static const unsigned short EXISTS;
    MediaTableModel(Playlist *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    Playlist *playlist;
};

#endif // MEDIATABLEMODEL_H
