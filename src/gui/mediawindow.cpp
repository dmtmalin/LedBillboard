#include "mediawindow.h"
#include "ui_mediawindow.h"
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/MediaListPlayer.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaList.h>


MediaWindow::MediaWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaWindow)
{
    ui->setupUi(this);
    this->mediaList = NULL;
    this->instance = new VlcInstance(VlcCommon::args(), this);
    this->player = new VlcMediaPlayer(instance);
    this->player->setVideoWidget(this->ui->video);
    this->ui->video->setMediaPlayer(this->player);
    this->playlist = new VlcMediaListPlayer(this->player, instance);
    this->playlist->setPlaybackMode(Vlc::Repeat);
}

MediaWindow::~MediaWindow()
{    
    if (this->mediaList != NULL)
        delete this->mediaList;
    delete this->playlist;
    delete this->player;
    delete this->instance;
    delete this->ui;
}

void MediaWindow::play()
{
    this->playlist->play();
}

void MediaWindow::stop()
{
    this->playlist->stop();
}
