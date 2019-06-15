#include "projectsettingdialog.h"
#include "utils/configurations.h"

#include <QFileDialog>
#include <QDir>

ProjectSettingDialog::ProjectSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectSettingDialog)
{
    ui->setupUi(this);

    // setup the button group
    ui->backendButtonGroup->setId(ui->kerasRadioButton, static_cast<int>(Backend::Keras));
    ui->backendButtonGroup->setId(ui->pyTorchRadioButton, static_cast<int>(Backend::Pytorch));

    connect(ui->locationBrowseButton, SIGNAL(clicked()), this, SLOT(browseFiles()));
    connect(ui->pythonBrowseButton, SIGNAL(clicked()), this, SLOT(browsePython()));
    connect(ui->tensorboardBrowseButton, SIGNAL(clicked()), this, SLOT(browseTensorboard()));
}

ProjectSettingDialog::~ProjectSettingDialog()
{
    delete ui;
}

void ProjectSettingDialog::browseFiles() const noexcept
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::Directory);
    if (fileDialog.exec()) {
        QStringList directories = fileDialog.selectedFiles();
        ui->locationLineEdit->setText(directories.front());
    }
}

void ProjectSettingDialog::browsePython() const noexcept
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::ExistingFile);
    fileDialog.setNameFilter("python.exe");
    if (fileDialog.exec()){
        QStringList files = fileDialog.selectedFiles();
        ui->pythonLocationEdit->setText(files.front());
    }
}

void ProjectSettingDialog::browseTensorboard() const noexcept
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::ExistingFile);
    fileDialog.setNameFilter("tensorboard.exe");
    if (fileDialog.exec()){
        QStringList files = fileDialog.selectedFiles();
        ui->tensorboardLocationEdit->setText(files.front());
    }
}

void ProjectSettingDialog::ConfigureSettingMode(ProjectCFG project_cfg)
{
    ui->projectNameLineEdit->setText(project_cfg.name);
    ui->projectNameLineEdit->setReadOnly(true);
    switch (project_cfg.backend) {
    case Backend::Keras:
        ui->kerasRadioButton->click();
        break;
    case Backend::Pytorch:
        ui->pyTorchRadioButton->click();
        break;
    }
    ui->kerasRadioButton->setEnabled(false);
    ui->pyTorchRadioButton->setEnabled(false);
    ui->locationLineEdit->setText(project_cfg.location);
    ui->locationLineEdit->setReadOnly(true);
    ui->locationBrowseButton->setEnabled(false);
//    ui->locationBrowseButton->setVisible(false);
    ui->pythonLocationEdit->setText(project_cfg.python_path);
    ui->tensorboardLocationEdit->setText(project_cfg.tensorboard_path);
}
