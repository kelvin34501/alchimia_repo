#ifndef PROJECTSETTINGDIALOG_H
#define PROJECTSETTINGDIALOG_H

#include "converter/converter.h"
#include "ui_projectsettingdialog.h"

#include <QDialog>


namespace Ui {
class ProjectSettingDialog;
}

class ProjectSettingDialog : public QDialog
{
    Q_OBJECT

public:
    QString projecName() const noexcept { return ui->projectNameLineEdit->text(); }
    Backend backend() const noexcept { return mBackend; }
    QString projectPath() const noexcept { return ui->locationLineEdit->text(); }
    QString pythonPath() const noexcept { return ui->pythonLocationEdit->text(); }
    QString tensorboardPath() const noexcept { return ui->tensorboardLocationEdit->text(); }

    explicit ProjectSettingDialog(QWidget *parent = nullptr);
    ~ProjectSettingDialog();

private slots:
    /**
    * Connected to the "Browse" button's clicked() signal
    */
    void browseFiles() const noexcept;
    void browsePython() const noexcept;
    void browseTensorboard() const noexcept;

private:
    Ui::ProjectSettingDialog *ui;
    Backend mBackend;
};

#endif // PROJECTSETTINGDIALOG_H
