#ifndef CONFIGURETESTDIALOG_H
#define CONFIGURETESTDIALOG_H

#include <QDialog>
#include "utils/configurations.h"
#include "modelcontrol/modelcontrol.h"

namespace Ui {
class ConfigureTestDialog;
}

class ConfigureTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureTestDialog(TestCFG test_cfg, QWidget *parent = nullptr, ModelControl *mc = nullptr);
    ~ConfigureTestDialog();
    TestCFG TestConfiguration();

private slots:
    void browseSaveDir();

private:
    void update();

    Ui::ConfigureTestDialog *ui;
    ModelControl *mc;
    TestCFG test_cfg;
};

#endif // CONFIGURETESTDIALOG_H
