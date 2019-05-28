#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projectsettingdialog.h"


using namespace project;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), mProjectControl(*this, *ui)
{
    ui->setupUi(this);
    connect(ui->actionNew_Project, SIGNAL(triggered()), &mProjectControl, SLOT(create_new_project()));
    connect(ui->actionSave_Project,SIGNAL(triggered()), &mProjectControl, SLOT(save_active_project()));
    // set up the toolbox
    QButtonGroup *buttonGroup = ui->toolBoxButtonGroup;
    buttonGroup->setId(ui->inputLayerButton, static_cast<int>(PartType::InputLayer));
    buttonGroup->setId(ui->denseButton, static_cast<int>(PartType::Dense));
    buttonGroup->setId(ui->conv2DButton, static_cast<int>(PartType::Conv2D));
    buttonGroup->setId(ui->maxPooling2DButton, static_cast<int>(PartType::MaxPooling2D));
    buttonGroup->setId(ui->activationButton, static_cast<int>(PartType::Activation));
    buttonGroup->setId(ui->dropoutButton, static_cast<int>(PartType::Dropout));
    buttonGroup->setId(ui->flattenButton, static_cast<int>(PartType::Flatten));
    buttonGroup->setId(ui->reshapeButton, static_cast<int>(PartType::Reshape));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mModelScene;
    delete mModelControl;
}
