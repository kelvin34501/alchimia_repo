#include "dataconfigurationdialog.h"
#include "ui_dataconfigurationdialog.h"

DataConfigurationDialog::DataConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataConfigurationDialog)
{
    ui->setupUi(this);
}

DataConfigurationDialog::~DataConfigurationDialog()
{
    delete ui;
}
