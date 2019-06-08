#ifndef DATACONFIGURATIONDIALOG_H
#define DATACONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class DataConfigurationDialog;
}

class DataConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataConfigurationDialog(QWidget *parent = nullptr);
    ~DataConfigurationDialog();

private:
    Ui::DataConfigurationDialog *ui;
};

#endif // DATACONFIGURATIONDIALOG_H
