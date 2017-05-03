#include "service/playlistcollectionservice.h"
#include "gui/playlistwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->ui->tabWidget->removeTab(0);
    this->ui->tabWidget->addTab(new PlaylistWidget, tr("Плейлисты"));

    connect(playlistCollectionService::Instance(), SIGNAL(successLoadFromService()), SLOT(slotSuccessAllPlaylist()));
    connect(playlistCollectionService::Instance(), SIGNAL(successDownloadMediaFiles()), SLOT(slotSuccessDownloadMediaFiles()));

    playlistCollectionService::Instance()->loadFromService();
}

MainWindow::~MainWindow()
{    
    delete this->ui;
}

void MainWindow::slotSuccessAllPlaylist()
{
    //ui->labelStatus->setText("Загрузка медиа...");
    playlistCollectionService::Instance()->DownloadMediaFiles();
}

void MainWindow::slotSuccessDownloadMediaFiles()
{
    //ui->labelStatus->setText("Плейлисты и медиа обновлены.");
}
