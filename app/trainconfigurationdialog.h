#ifndef TRAINCONFIGURATIONDIALOG_H
#define TRAINCONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class TrainConfigurationDialog;
}

class TrainConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainConfigurationDialog(QWidget *parent = nullptr);
    ~TrainConfigurationDialog();

private:
    Ui::TrainConfigurationDialog *ui;
};

#endif // TRAINCONFIGURATIONDIALOG_H
