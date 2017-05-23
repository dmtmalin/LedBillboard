#ifndef BILLBOARDSERVICE_H
#define BILLBOARDSERVICE_H

#include <QObject>
#include <singleton.h>

namespace Service {
class BillboardService;
}

class MediaWindow;
class Playlist;
class QString;

class BillboardService : public QObject
{
    Q_OBJECT
public:
    explicit BillboardService(QObject *parent = 0);
    ~BillboardService();

    void show();
    void hide();    
    void play(Playlist *playlist);

private:
    MediaWindow *mediaView;
    Playlist *playlist;
    void playNext();

private slots:
    void slotEndMediaPlay();
};

typedef Singleton<BillboardService> billboardService;

#endif // BILLBOARDSERVICE_H
