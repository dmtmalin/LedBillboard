#include <QApplication>
#include <QWindow>
#include "gui/mediawindow.h"
#include "settings.h"
#include "billboardservice.h"

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

BillboardService::BillboardService()
{
    this->mediaView = new MediaWindow();
}

BillboardService::~BillboardService()
{
    delete this->mediaView;
}
