#include "modelconfigurationdialog.h"
#include "ui_modelconfigurationdialog.h"

ModelConfigurationDialog::ModelConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelConfigurationDialog)
{
    ui->setupUi(this);
}

ModelConfigurationDialog::~ModelConfigurationDialog()
{
    delete ui;
}
