#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <QWidget>

namespace Ui {
class MediaWindow;
}

class MediaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MediaWindow(QWidget *parent = 0);
    ~MediaWindow();

private:
    Ui::MediaWindow *ui;
};

#endif // BILLBOARD_H
