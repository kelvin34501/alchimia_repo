#include <QGraphicsView>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphmodel/graphmodel_name.h"
#include "utils/enum_cast.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mGraphModel(new GraphModel(Backend::Keras))
{
    ui->setupUi(this);
    ui->setupUi(this);
    mModelScene = new ModelScene(*ui->toolBoxButtonGroup, *mGraphModel);
    ui->graphicsView->setScene(mModelScene);

    // set up the toolbox
    QButtonGroup *buttonGroup = ui->toolBoxButtonGroup;
    buttonGroup->setId(ui->toolButton, as_integer(PartType::InputLayer));
    buttonGroup->setId(ui->toolButton_2, as_integer(PartType::Dense));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mModelScene;
}
