#include "mediawindow.h"
#include "ui_mediawindow.h"
#include "model/mediacontent.h"
#include <QDebug>
#include <QFile>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/Media.h>

MediaWindow::MediaWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaWindow)
{
    ui->setupUi(this);
    this->media = NULL;
    this->instance = new VlcInstance(VlcCommon::args(), this);
    this->player = new VlcMediaPlayer(this->instance);
    this->player->setVideoWidget(this->ui->video);

    this->ui->video->setMediaPlayer(this->player);

    connect(this->player, SIGNAL(end()), SLOT(slotEnd()));
}

void MediaWindow::play(MediaContent *content)
{       
    QString location = content->getFileName();
    if (QFile::exists(location)) {
        if (this->media != NULL)
            delete this->media;
        this->media = new VlcMedia(location, true, this->instance);
        this->player->open(this->media);
    }
    else {
        qWarning() << QString("Can't play file %1. File not exists.").arg(location);
    }
}

void MediaWindow::slotEnd()
{
    emit end();
}

MediaWindow::~MediaWindow()
{
    if (this->media != NULL)
        delete this->media;
    delete this->player;
    delete this->instance;
    delete this->ui;
}
