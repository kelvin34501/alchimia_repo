#include "tbvisuaizationdialog.h"
#include "ui_tbvisuaizationdialog.h"
#include "modelcontrol/modelcontrol.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

TBVisuaizationDialog::TBVisuaizationDialog(QWidget *parent, ModelControl *mc) :
    QDialog(parent),
    ui(new Ui::TBVisuaizationDialog)
{
    ui->setupUi(this);
    this->mc = mc;

    connect(ui->existsRadioButton, SIGNAL(clicked()), this, SLOT(updateExists()));
    connect(ui->currentRadioButton, SIGNAL(clicked()), this, SLOT(updateCurrent()));
    connect(ui->logdirBrowseButton, SIGNAL(clicked()), this, SLOT(browseLogDir()));
    // TODO: link browser, link radio buttons
}

TBVisuaizationDialog::~TBVisuaizationDialog()
{
    delete ui;
}

void TBVisuaizationDialog::updateExists()
{
    ui->infoLabel->setText("Visualize the logs in the given directory.");
}

void TBVisuaizationDialog::updateCurrent()
{
    QMessageBox msgBox;
    int ret;
    ui->infoLabel->setText("Visualize the currenctly loaded model.\nThe logs will be saved in the given directory.");
    if(!mc->modelSet()){
        msgBox.setText("Model not loaded.");
        msgBox.setText("Do you want to compile the model or load existing ones?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Open | QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Save, "Compile");
        msgBox.setButtonText(QMessageBox::Open, "Load");
        ret = msgBox.exec();
        switch(ret)
        {
        case QMessageBox::Save:
            mc->compileModelPublic();
            break;
        case QMessageBox::Open:
            mc->configureModelPublic();
            break;
        case QMessageBox::Cancel:
            ui->existsRadioButton->click();
            break;
        }
    }
}

void TBVisuaizationDialog::browseLogDir()
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::Directory);
    if (fileDialog.exec()){
        QStringList files = fileDialog.selectedFiles();
        ui->logdirLineEdit->setText(files.front());
    }
}
