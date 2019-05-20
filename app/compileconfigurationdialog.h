#ifndef COMPILECONFIGURATIONDIALOG_H
#define COMPILECONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class CompileConfigurationDialog;
}

class CompileConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompileConfigurationDialog(QWidget *parent = nullptr);
    ~CompileConfigurationDialog();

private slots:
    void updateFiles() const noexcept;
    void setJson() noexcept;
    void setYaml() noexcept;

private:
    Ui::CompileConfigurationDialog *ui;
    QString suffix;
};

#endif // COMPILECONFIGURATIONDIALOG_H
