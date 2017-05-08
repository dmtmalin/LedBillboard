#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <QWidget>

namespace Ui {
class MediaWindow;
}

class VlcInstance;
class VlcMediaPlayer;
class VlcMediaListPlayer;
class VlcMediaList;

class MediaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MediaWindow(QWidget *parent = 0);
    ~MediaWindow();

public:
    void play();
    void pause();
    void stop();

private:
    Ui::MediaWindow *ui;
    VlcInstance *instance;
    VlcMediaPlayer *player;
    VlcMediaList *mediaList;
    VlcMediaListPlayer *playlist;
};

#endif // BILLBOARD_H
