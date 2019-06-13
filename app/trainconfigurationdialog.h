#ifndef TRAINCONFIGURATIONDIALOG_H
#define TRAINCONFIGURATIONDIALOG_H

#include <QDialog>
#include "utils/configurations.h"
#include "modelcontrol/modelcontrol.h"

namespace Ui {
class TrainConfigurationDialog;
}

class TrainConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainConfigurationDialog(TrainCFG cfg, QWidget *parent = nullptr, ModelControl *mc = nullptr);
    ~TrainConfigurationDialog();

private slots:
    void browseSaveDir();
    void updateBatchSlider(int);
    void updateSplitSlider(int);
    void updateSplitText(QString);

private:
    void update();

    Ui::TrainConfigurationDialog *ui;
    ModelControl *mc;
    TrainCFG train_cfg;
};

#endif // TRAINCONFIGURATIONDIALOG_H
