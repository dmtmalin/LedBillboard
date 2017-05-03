#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>

namespace Ui {
class PlaylistWidget;
}

class QModelIndex;
class PlaylistTableModel;
class MediaTableModel;

class PlaylistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistWidget(QWidget *parent = 0);
    ~PlaylistWidget();

private:
    Ui::PlaylistWidget *ui;
    PlaylistTableModel *playlistTableModel;
    MediaTableModel *mediaTableModel;
private slots:
    void slotTableViewPlaylistClicked(const QModelIndex &index);

};

#endif // PLAYLISTWIDGET_H
