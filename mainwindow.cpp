#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphmodel/graphmodel_name.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mEditorControl(&mModelScene)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&mModelScene);

    mModelScene.setEditorControl(&mEditorControl);
    mEditorControl.setToolboxButtonGroup(ui->toolBoxButtonGroup);

    // set up the toolbox
    QButtonGroup *buttonGroup = ui->toolBoxButtonGroup;
    buttonGroup->setId(ui->toolButton, PartType::InputLayer);
    buttonGroup->setId(ui->toolButton_2, PartType::Dense);

    connect(buttonGroup, SIGNAL(buttonClicked(int)), &mEditorControl, SLOT(selectTemplate(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
