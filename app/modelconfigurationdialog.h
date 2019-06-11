#ifndef MODELCONFIGURATIONDIALOG_H
#define MODELCONFIGURATIONDIALOG_H

#include <QDialog>
#include "utils/configurations.h"
#include "ui_modelconfigurationdialog.h"

namespace Ui {
class ModelConfigurationDialog;
}

class ModelConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    QString archiPath() const noexcept { return ui->archiPathLineEdit->text(); }
    QString weightPath() const noexcept { return ui->weightPathLineEdit->text(); }

    explicit ModelConfigurationDialog(ModelCFG model_cfg, QWidget *parent = nullptr);
    ~ModelConfigurationDialog();

private slots:
    void browseArchi() const noexcept;
    void browseWeight() const noexcept;


private:
    Ui::ModelConfigurationDialog *ui;
};

#endif // MODELCONFIGURATIONDIALOG_H
