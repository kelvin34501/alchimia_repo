#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myScene.setSceneRect(ui->graphicsView->geometry());
    ui->graphicsView->setScene(&myScene);
    myScene.addItem(new DiagramItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}
