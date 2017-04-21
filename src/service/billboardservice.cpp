#include "gui/mediawindow.h"
#include "billboardservice.h"

void BillboardService::show()
{
    this->mediaView->showFullScreen();
}

BillboardService::BillboardService()
{
    this->mediaView = new MediaWindow();
    //this->billboard->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //this->billboard->isFullScreen()
}

BillboardService::~BillboardService()
{
    delete this->mediaView;
}
