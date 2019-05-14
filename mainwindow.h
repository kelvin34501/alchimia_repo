#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "modelscene.h"
#include "graphmodel/graphmodel.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ModelScene *mModelScene = nullptr;

    /**
    * @var A mock-up of the real GraphModel in a Project instance
    */
    GraphModel *mGraphModel;
};

#endif // MAINWINDOW_H
