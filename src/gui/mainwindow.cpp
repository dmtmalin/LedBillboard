#include "model/playlistcollection.h"
#include "model/playlist.h"
#include "service/billboardservice.h"
#include "service/playlistcollectionservice.h"
#include "service/mediaservice.h"
#include "gui/playlistwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->ui->tabWidget->addTab(new PlaylistWidget, tr("Плейлисты"));    

    connect(this->ui->buttonShowBoard, SIGNAL(pressed()), SLOT(slotPressedButtonShowBoard()));
    connect(this->ui->buttonHideBoard, SIGNAL(pressed()), SLOT(slotPressedButtonHideBoard()));

    connect(playlistCollectionService::Instance(), SIGNAL(successLoadFromService()), SLOT(slotSuccessAllPlaylist()));
    connect(mediaService::Instance(), SIGNAL(finishedDownloadMediaFiles()), SLOT(slotFinishedDownloadMediaFiles()));

    playlistCollectionService::Instance()->loadFromService();
}

MainWindow::~MainWindow()
{    
    delete this->ui;
}

/*
 * SLOTS
*/
void MainWindow::slotSuccessAllPlaylist()
{
    //ui->labelStatus->setText("Загрузка медиа...");
    mediaService::Instance()->DownloadMediaFiles();
}

void MainWindow::slotFinishedDownloadMediaFiles()
{
    //ui->labelStatus->setText("Плейлисты и медиа обновлены.");
    int count = playlistCollectionService::Instance()->getCollection()->count();
    if (count > 0) {
        Playlist *playlist = playlistCollectionService::Instance()->getCollection()->getPlaylist(0);
        billboardService::Instance()->play(playlist);
    }
}

void MainWindow::slotPressedButtonShowBoard()
{
    billboardService::Instance()->show();
}

void MainWindow::slotPressedButtonHideBoard()
{
    billboardService::Instance()->hide();
}
