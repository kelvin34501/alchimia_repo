#ifndef PROJECTSETTINGDIALOG_H
#define PROJECTSETTINGDIALOG_H

#include "converter/converter.h"
#include "ui_projectsettingdialog.h"
#include "utils/configurations.h"

#include <QDialog>


namespace Ui {
class ProjectSettingDialog;
}

class ProjectSettingDialog : public QDialog
{
    Q_OBJECT

public:
    QString projecName() const noexcept { return ui->projectNameLineEdit->text(); }
    Backend backend() const noexcept { return static_cast<Backend>(ui->backendButtonGroup->checkedId()); }
    QString projectPath() const noexcept { return ui->locationLineEdit->text(); }
    QString pythonPath() const noexcept { return ui->pythonLocationEdit->text(); }
    QString tensorboardPath() const noexcept { return ui->tensorboardLocationEdit->text(); }
    explicit ProjectSettingDialog(QWidget *parent = nullptr);
    ~ProjectSettingDialog();
    void ConfigureSettingMode(ProjectCFG project_cfg);

private slots:
    /**
    * Connected to the "Browse" button's clicked() signal
    */
    void browseFiles() const noexcept;
    void browsePython() const noexcept;
    void browseTensorboard() const noexcept;

private:
    Ui::ProjectSettingDialog *ui;
};

#endif // PROJECTSETTINGDIALOG_H
