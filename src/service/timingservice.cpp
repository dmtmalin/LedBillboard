#include <QTimer>
#include <QtDebug>
#include "service/apiservice.h"
#include "service/playlistcollectionservice.h"
#include "settings.h"
#include "timingservice.h"

TimingService::TimingService(QObject *parent) : QObject(parent)
{
    this->retryTimer = new QTimer(this);
}

TimingService::~TimingService()
{
    this->retryTimer->stop();
    delete this->retryTimer;
}

void TimingService::retryLogin()
{
    int msec = settings::Instance()->getValue(Settings::RETRY).toInt();
    int sec = msec / 1000;
    qInfo() << QString("Retry login in %1 sec.").arg(sec);
    this->retryTimer->singleShot(msec, apiService::Instance(), apiService::Instance()->login);
}

void TimingService::retryLoadPlaylistCollection()
{
    int msec = settings::Instance()->getValue(Settings::RETRY).toInt();
    int sec = msec / 1000;
    qInfo() << QString("---Retry load playlist collection in %1 sec. Relogin.---").arg(sec);
    this->retryTimer->singleShot(msec, playlistCollectionService::Instance()
                                 , playlistCollectionService::Instance()->loadFromService);

}
