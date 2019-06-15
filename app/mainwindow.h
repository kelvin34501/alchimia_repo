#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "modelscene.h"
#include "project/project_control.h"
#include "modelcontrol/modelcontrol.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ModelScene *modelScene() const noexcept { return mModelScene; }
    ModelControl *modelControl() const noexcept { return mModelControl; }
    void setModelScene(ModelScene * modelScene) noexcept { mModelScene = modelScene; }
    void setModelControl(ModelControl *modelControl) noexcept { mModelControl = modelControl; }

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ModelScene *mModelScene = nullptr;
    project_control mProjectControl;
    ModelControl *mModelControl = nullptr;
};

#endif // MAINWINDOW_H
