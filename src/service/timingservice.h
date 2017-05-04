#ifndef TIMINGSERVICE_H
#define TIMINGSERVICE_H

#include <QObject>
#include "singleton.h"

class QTimer;


class TimingService : public QObject
{
    Q_OBJECT
public:
    explicit TimingService(QObject *parent = 0);
    ~TimingService();
    void retryLogin();
    void retryLoadPlaylistCollection();

private:
    QTimer *retryTimer;
};

typedef Singleton<TimingService> timingService;

#endif // TIMINGSERVICE_H
