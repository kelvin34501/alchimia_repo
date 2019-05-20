#include "compileconfigurationdialog.h"
#include "ui_compileconfigurationdialog.h"

CompileConfigurationDialog::CompileConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompileConfigurationDialog)
{
    ui->setupUi(this);
    connect(ui->architectureNameEdit, SIGNAL(textChanged(QString)), this, SLOT(updateFiles(QString)));
    connect(ui->jsonButton, SIGNAL(clicked()), this, SLOT(setJson()));
    connect(ui->yamlButton, SIGNAL(clicked()), this, SLOT(setYaml()));
    suffix = ".json";
    updateFiles("");
}

CompileConfigurationDialog::~CompileConfigurationDialog()
{
    delete ui;
}

void CompileConfigurationDialog::updateFiles(QString dummy) const noexcept{
    QString name = ui->architectureNameEdit->text();
    ui->genFile->setText(name + "/" + name + suffix);
    ui->pyFile->setText(name + "/" + name + ".gen");
}

void CompileConfigurationDialog::setJson() noexcept{
    suffix = ".json";
    updateFiles("");
}

void CompileConfigurationDialog::setYaml() noexcept{
    suffix = ".yaml";
    updateFiles("");
}
