#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <QWidget>

namespace Ui {
class MediaWindow;
}

class VlcInstance;
class VlcMediaPlayer;
class VlcMedia;
class MediaContent;

class MediaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MediaWindow(QWidget *parent = 0);
    ~MediaWindow();

public:
    void play(MediaContent *content);

private:
    Ui::MediaWindow *ui;
    VlcInstance *instance;
    VlcMediaPlayer *player;
    VlcMedia *media;

private slots:
    void slotEnd();

signals:
    void end();
};

#endif // BILLBOARD_H
