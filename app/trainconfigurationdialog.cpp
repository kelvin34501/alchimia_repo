#include "trainconfigurationdialog.h"
#include "ui_trainconfigurationdialog.h"

TrainConfigurationDialog::TrainConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainConfigurationDialog)
{
    ui->setupUi(this);
}

TrainConfigurationDialog::~TrainConfigurationDialog()
{
    delete ui;
}
