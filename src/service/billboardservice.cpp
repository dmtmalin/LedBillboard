#include <QApplication>
#include <QWindow>
#include <QFile>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaList.h>
#include "model/playlist.h"
#include "model/mediacontent.h"
#include "gui/mediawindow.h"
#include "settings.h"
#include "billboardservice.h"

BillboardService::BillboardService(QObject *parent) :
    QObject(parent)
{
    this->mediaView = new MediaWindow();
    connect(this->mediaView, SIGNAL(end()), SLOT(slotEndMediaPlay()));
}

void BillboardService::show()
{
    this->mediaView->show();
    int screen = settings::Instance()->getValue(Settings::SCREEN).toInt();
    int screenCount = qApp->screens().count();
    if (screenCount > screen)
        this->mediaView->windowHandle()->setScreen(qApp->screens()[screen]);
    this->mediaView->showFullScreen();
}

void BillboardService::hide()
{
    this->mediaView->hide();
}

void BillboardService::play(Playlist *playlist)
{
    this->playlist = playlist;
    playNext();
}

void BillboardService::playNext()
{
    if (this->playlist == NULL)
        return;
    MediaContent *media = this->playlist->nextMedia();
    this->mediaView->play(media);
}

void BillboardService::slotEndMediaPlay()
{
    playNext();
}

BillboardService::~BillboardService()
{
    delete this->mediaView;
}
