#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphmodel/graphmodel_name.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mModelScene = new ModelScene(*ui->toolBoxButtonGroup);
    ui->graphicsView->setScene(mModelScene);

    // set up the toolbox
    QButtonGroup *buttonGroup = ui->toolBoxButtonGroup;
    buttonGroup->setId(ui->toolButton, PartType::InputLayer);
    buttonGroup->setId(ui->toolButton_2, PartType::Dense);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mModelScene;
}
