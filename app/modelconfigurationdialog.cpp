#include "modelconfigurationdialog.h"
#include "ui_modelconfigurationdialog.h"

#include <QFileDialog>
#include <QDir>

ModelConfigurationDialog::ModelConfigurationDialog(ModelCFG model_cfg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelConfigurationDialog)
{

    ui->setupUi(this);
    ui->archiPathLineEdit->setText(QString::fromStdString(model_cfg.archi_path));
    ui->weightPathLineEdit->setText(QString::fromStdString(model_cfg.weight_path));
    connect(ui->archiBrowseButton, SIGNAL(clicked()), this, SLOT(browseArchi()));
    connect(ui->weightBrowseButton, SIGNAL(clicked()), this, SLOT(browseWeight()));
}

ModelConfigurationDialog::~ModelConfigurationDialog()
{
    delete ui;
}


void ModelConfigurationDialog::browseArchi() const noexcept
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::ExistingFile);
    fileDialog.setNameFilter("*.json"); // TODO: include yaml
    if (fileDialog.exec()){
        QStringList files = fileDialog.selectedFiles();
        ui->archiPathLineEdit->setText(files.front());
    }
}

void ModelConfigurationDialog::browseWeight() const noexcept
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::ExistingFile);
    fileDialog.setNameFilter("*.h5");
    if (fileDialog.exec()){
        QStringList files = fileDialog.selectedFiles();
        ui->weightPathLineEdit->setText(files.front());
    }
}
