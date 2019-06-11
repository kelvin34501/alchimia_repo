#include "dataconfigurationdialog.h"
#include "ui_dataconfigurationdialog.h"
#include "project/project_control.h"
#include <string>
#include <vector>
#include <QMessageBox>
#include <iostream>

using namespace project;

DataConfigurationDialog::DataConfigurationDialog(DataCFG data_cfg, QWidget *parent, project_control *pc) :
    QDialog(parent),
    ui(new Ui::DataConfigurationDialog)
{
    ui->setupUi(this);
    this->pc = pc;

    connect(ui->updateInputButton, SIGNAL(clicked()), this, SLOT(updateInputShape()));
    connect(ui->datasetComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(updateDataset(const QString)));
}

DataConfigurationDialog::~DataConfigurationDialog()
{
    delete ui;
}

void DataConfigurationDialog::updateDataset(const QString name)
{
    QString shape;
    QString size;
    cout << name.toStdString() << endl;
    if(name == "cifar10"){
        shape = "(32,32,3)";
        size = "Dataset of 50,000 32x32 color training images,\nlabeled over 10 categories,\nand 10,000 test images.";
    }
    else if(name == "cifar100"){
        shape = "(32,32,3)";
        size = "Dataset of 50,000 32x32 color training images,\nlabeled over 100 categories,\nand 10,000 test images.";
    }
    else if(name == "imdb"){
        // TODO: unable to use
        shape = "sequence";
        size = "Dataset of 25,000 movies reviews from IMDB,\nlabeled by sentiment (positive/negative).";
    }
    else if(name == "reuters"){
        // TODO: unable to use
        shape = "sequence";
        size = "Dataset of 11,228 newswires from Reuters,\nlabeled over 46 topics.";
    }
    else if(name == "mnist"){
        shape = "(28,28)";
        size = "Dataset of 60,000 28x28 grayscale images of the 10 digits,\nalong with a test set of 10,000 images.";
    }
    else if(name == "fashion_mnist"){
        shape = "(28,28)";
        size = "Dataset of 60,000 28x28 grayscale images of 10 fashion categories,\nalong with a test set of 10,000 images.";
    }
    else if(name == "boston_bousing"){
        shape = "(13)";
        size = "Samples contain 13 attributes of houses at different locations\naround the Boston suburbs in the late 1970s.";
    }
    else{
        shape = "";
        size = "";
    }
    ui->datasetShapeLabel->setText(shape);
    ui->datasetSizeLabel->setText(size);
}

void DataConfigurationDialog::updateInputShape()
{
    vector<int> idx = pc->get_active_project()->graph_mdl->get_input_parts_idx();
    vector<string> shapes = pc->get_active_project()->graph_mdl->get_input_parts_shape();
    string shape = ui->datasetShapeLabel->text().toStdString();
    QMessageBox msgBox;
    if(shape == ""){
        msgBox.setText("No dataset selected!");
        msgBox.exec();
        return;
    }

    msgBox.setText("This will update input shapes of all input parts.");
    msgBox.setInformativeText("Do want to continue to update input shapes?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if(ret != QMessageBox::Yes){
        return;
    }

    for(int i=0; i<shapes.size(); i++)
    {
//        try {
        if(shape != shapes[i])
        {
            pc->get_active_project()->graph_mdl->editPart(idx[i], "input_shape", shape);
        }
//        } catch () {

//        }
    }
}
