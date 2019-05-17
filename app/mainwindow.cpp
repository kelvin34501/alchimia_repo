#include <QGraphicsView>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphmodel/graphmodel_name.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mGraphModel(new GraphModel(Backend::Keras))
{
    ui->setupUi(this);
    mModelScene = new ModelScene(*ui->toolBoxButtonGroup, *mGraphModel,
                                 *ui->connectButton);
    ui->graphicsView->setScene(mModelScene);

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
    // set up the connect button
    connect(ui->connectButton, SIGNAL(clicked(bool)), mModelScene, SLOT(startConnection(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mModelScene;
}
