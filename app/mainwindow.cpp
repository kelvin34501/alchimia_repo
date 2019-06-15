#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projectsettingdialog.h"
#include <QIcon>

using namespace project;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), mProjectControl(*this, *ui)
{
    ui->setupUi(this);
    connect(ui->actionNew_Project, SIGNAL(triggered()), &mProjectControl, SLOT(create_new_project()));
    connect(ui->actionSave_Project,SIGNAL(triggered()), &mProjectControl, SLOT(save_active_project()));
    connect(ui->actionClose_Project,SIGNAL(triggered()), &mProjectControl, SLOT(close_project()));
    connect(ui->actionOpen_Project,SIGNAL(triggered()), &mProjectControl, SLOT(open_project()));
    connect(ui->actionProject_Setting, SIGNAL(triggered()), &mProjectControl, SLOT(ConfigureSetting()));
    // set up the toolbox
    QButtonGroup *buttonGroup = ui->toolBoxButtonGroup;
    buttonGroup->setId(ui->inputLayerButton, static_cast<int>(PartType::InputLayer));
    buttonGroup->button(1)->setIcon(QIcon(":/resources/io-layers.svg"));
    buttonGroup->button(1)->setIconSize(QSize(60,60));
    buttonGroup->setId(ui->denseButton, static_cast<int>(PartType::Dense));
    buttonGroup->button(2)->setIcon(QIcon(":/resources/Dense.svg"));
    buttonGroup->button(2)->setIconSize(QSize(60,60));
    buttonGroup->setId(ui->conv2DButton, static_cast<int>(PartType::Conv2D));
    buttonGroup->button(3)->setIcon(QIcon(":/resources/convolutional-layers.svg"));
    buttonGroup->button(3)->setIconSize(QSize(60,60));
    buttonGroup->setId(ui->maxPooling2DButton, static_cast<int>(PartType::MaxPooling2D));
    buttonGroup->button(4)->setIcon(QIcon(":/resources/convolutional-layers.svg"));
    buttonGroup->button(4)->setIconSize(QSize(60,60));
    buttonGroup->setId(ui->activationButton, static_cast<int>(PartType::Activation));
    buttonGroup->button(5)->setIcon(QIcon(":/resources/Activation.svg"));
    buttonGroup->button(5)->setIconSize(QSize(60,60));
    buttonGroup->setId(ui->dropoutButton, static_cast<int>(PartType::Dropout));
    buttonGroup->button(6)->setIcon(QIcon(":/resources/Dropout.svg"));
    buttonGroup->button(6)->setIconSize(QSize(60,60));
    buttonGroup->setId(ui->flattenButton, static_cast<int>(PartType::Flatten));
    buttonGroup->button(7)->setIcon(QIcon(":/resources/Flatten.svg"));
    buttonGroup->button(7)->setIconSize(QSize(60,60));
    buttonGroup->setId(ui->reshapeButton, static_cast<int>(PartType::Reshape));
    buttonGroup->button(8)->setIcon(QIcon(":/resources/core-layers.png"));
    buttonGroup->button(8)->setIconSize(QSize(60,60));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mModelScene;
    delete mModelControl;
}
