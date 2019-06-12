#ifndef TBVISUAIZATIONDIALOG_H
#define TBVISUAIZATIONDIALOG_H

#include <QDialog>
#include "ui_tbvisuaizationdialog.h"
#include "modelcontrol/modelcontrol.h"

namespace Ui {
class TBVisuaizationDialog;
}

class TBVisuaizationDialog : public QDialog
{
    Q_OBJECT

public:
    QString logDir() const noexcept { return ui->logdirLineEdit->text(); }

    explicit TBVisuaizationDialog(QWidget *parent = nullptr, ModelControl *mc = nullptr);
    ~TBVisuaizationDialog();

private slots:
    void updateExists();
    void updateCurrent();
    void browseLogDir();

private:
    Ui::TBVisuaizationDialog *ui;
    ModelControl *mc;
};

#endif // TBVISUAIZATIONDIALOG_H
