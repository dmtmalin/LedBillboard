#include "service/apiservice.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ApiService::Instance().login();
}

MainWindow::~MainWindow()
{
    delete ui;
}
