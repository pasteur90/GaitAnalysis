#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sensordatacollector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SensorDataCollector _collector;
    _collector.deviceSearch();
}

MainWindow::~MainWindow()
{

    delete ui;
}
