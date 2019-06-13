#ifndef DATACONFIGURATIONDIALOG_H
#define DATACONFIGURATIONDIALOG_H

#include <QDialog>
#include <QObject>
#include "project/project_control.h"
#include "utils/configurations.h"
#include "ui_dataconfigurationdialog.h"

using namespace project;

namespace Ui {
class DataConfigurationDialog;
}

class DataConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    QString datasetName() const noexcept { return ui->datasetComboBox->currentText(); }

    explicit DataConfigurationDialog(DataCFG data_cfg, QWidget *parent = nullptr, project_control *pc = nullptr);
    ~DataConfigurationDialog();

private slots:
    void updateInputShape();
    void updateDataset(const QString);

signals:
    void modelUpdated();

private:
    Ui::DataConfigurationDialog *ui;
    project_control *pc;
};

#endif // DATACONFIGURATIONDIALOG_H
