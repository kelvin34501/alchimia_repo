#include "projectsettingdialog.h"

#include <QFileDialog>
#include <QDir>

ProjectSettingDialog::ProjectSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectSettingDialog)
{
    ui->setupUi(this);
    mBackend = Backend::Keras;
    connect(ui->browsePushButton, SIGNAL(clicked()), this, SLOT(browseFiles()));
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
