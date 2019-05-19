#include "projectsettingdialog.h"

#include <QFileDialog>


ProjectSettingDialog::ProjectSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectSettingDialog)
{
    ui->setupUi(this);
    mBackend = Backend::Keras;
    connect(ui->browsePushButton, SIGNAL(clicked()), this, SLOT(browseFiles()));
}

ProjectSettingDialog::~ProjectSettingDialog()
{
    delete ui;
}

void ProjectSettingDialog::browseFiles() const noexcept
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::Directory);
    if (fileDialog.exec()) {
        QStringList directories = fileDialog.selectedFiles();
        ui->locationLineEdit->setText(directories.front());
    }
}
