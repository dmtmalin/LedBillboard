#include "mediawindow.h"
#include "ui_mediawindow.h"

MediaWindow::MediaWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaWindow)
{
    ui->setupUi(this);
}

MediaWindow::~MediaWindow()
{
    delete ui;
}
