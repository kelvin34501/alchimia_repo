#ifndef MODELCONFIGURATIONDIALOG_H
#define MODELCONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ModelConfigurationDialog;
}

class ModelConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModelConfigurationDialog(QWidget *parent = nullptr);
    ~ModelConfigurationDialog();

private:
    Ui::ModelConfigurationDialog *ui;
};

#endif // MODELCONFIGURATIONDIALOG_H
