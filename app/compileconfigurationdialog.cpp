#include "compileconfigurationdialog.h"
#include "ui_compileconfigurationdialog.h"

CompileConfigurationDialog::CompileConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompileConfigurationDialog)
{
    ui->setupUi(this);
    connect(ui->architectureNameEdit, SIGNAL(textChanged()), this, SLOT(updateFiles));
    connect(ui->jsonButton, SIGNAL)
}

CompileConfigurationDialog::~CompileConfigurationDialog()
{
    delete ui;
}

void CompileConfigurationDialog::updateFiles() const noexcept{
    QString name = ui->architectureNameEdit->text();
    ui->genFile->setText(name + "/" + name + ".");
}

void CompileConfigurationDialog::setJson() noexcept{
    suffix = ".json";

}

void CompileConfigurationDialog::setYaml() noexcept{
    suffix = ".yaml";
}
