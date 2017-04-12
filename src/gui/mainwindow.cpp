#include "service/billboardservice.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BillboardService::Instance().show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
