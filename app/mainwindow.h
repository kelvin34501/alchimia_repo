#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "modelscene.h"
#include "project/project_control.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setModelScene(ModelScene * modelScene) noexcept { mModelScene = modelScene; }

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ModelScene *mModelScene = nullptr;
    project_control mProjectControl;
};

#endif // MAINWINDOW_H
