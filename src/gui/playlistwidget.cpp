#include <QModelIndex>
#include "model/tableview/playlisttablemodel.h"
#include "model/tableview/mediatablemodel.h"
#include "model/playlistcollection.h"
#include "model/playlist.h"
#include "service/playlistcollectionservice.h"
#include "playlistwidget.h"
#include "ui_playlistwidget.h"

PlaylistWidget::PlaylistWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistWidget)
{
    ui->setupUi(this);

    this->mediaTableModel = NULL;

    PlaylistCollection *collection = playlistCollectionService::Instance()->getCollection();
    this->playlistTableModel = new PlaylistTableModel(collection);
    this->ui->tableViewPlaylist->setModel(this->playlistTableModel);

    connect(this->ui->tableViewPlaylist, SIGNAL(clicked(const QModelIndex&)), SLOT(slotTableViewPlaylistClicked(const QModelIndex&)));
}

PlaylistWidget::~PlaylistWidget()
{
    delete ui;
}

void PlaylistWidget::slotTableViewPlaylistClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    QObject *obj = qvariant_cast<QObject *>(index.data(Qt::UserRole));
    Playlist *playlist = qobject_cast<Playlist *>(obj);

    if(this->mediaTableModel != NULL) {
        delete this->mediaTableModel;
    }
    this->mediaTableModel = new MediaTableModel(playlist);
    this->ui->tableViewMedia->setModel(this->mediaTableModel);
}
