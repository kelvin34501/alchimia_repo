#ifndef TRAINCONFIGURATIONDIALOG_H
#define TRAINCONFIGURATIONDIALOG_H

#include <QDialog>
#include "utils/configurations.h"
#include "modelcontrol/modelcontrol.h"
#include "ui_trainconfigurationdialog.h"

namespace Ui {
class TrainConfigurationDialog;
}

class TrainConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainConfigurationDialog(TrainCFG cfg, QWidget *parent = nullptr, ModelControl *mc = nullptr);
    ~TrainConfigurationDialog();
    TrainCFG TrainConfiguration();

private slots:
    void browseSaveDir();
    void browseLogDir();
    void updateBatchSlider(int);
    void updateSplitSlider(int);
    // void updateSplitText(QString);

private:
    void update();

    Ui::TrainConfigurationDialog *ui;
    ModelControl *mc;
    TrainCFG train_cfg;
    QMap<string, QCheckBox*> metrics;
};

#endif // TRAINCONFIGURATIONDIALOG_H
