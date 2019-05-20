#ifndef COMPILECONFIGURATIONDIALOG_H
#define COMPILECONFIGURATIONDIALOG_H

#include "ui_compileconfigurationdialog.h"

#include <QDialog>

namespace Ui {
class CompileConfigurationDialog;
}

class CompileConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompileConfigurationDialog(QWidget *parent = nullptr);
    QString pyFile() const noexcept { return ui->pyFile->text(); }
    QString genFile() const noexcept { return ui->genFile->text(); }
    QString archiName() const noexcept { return ui->architectureNameEdit->text(); }
    ~CompileConfigurationDialog();

private slots:
    void updateFiles(QString dummy) const noexcept;
    void setJson() noexcept;
    void setYaml() noexcept;

private:
    Ui::CompileConfigurationDialog *ui;
    QString suffix;
};

#endif // COMPILECONFIGURATIONDIALOG_H
