#include "mainwindow.h"
#include <QApplication>

#include <project/project_object.h>

int main(int argc, char *argv[])
{
    project::project_object p(QString(""), QString("keras"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
