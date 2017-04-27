#include "service/playlistcollectionservice.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(playlistCollectionService::Instance(), SIGNAL(successLoadFromService()), SLOT(slotSuccessAllPlaylist()));

    playlistCollectionService::Instance()->loadFromService();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotSuccessAllPlaylist()
{
    playlistCollectionService::Instance()->DownloadMediaFiles();
}
