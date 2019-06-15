#include "pythonadapter.h"
#include <iostream>
#include <cstring>
#include <QtCore/QCoreApplication>
#include <QtGui/QDesktopServices>
#include <QtCore/QProcess>
#include <QtCore/QStringList>
#include <QUrl>

using namespace std;

// TODO: perfect the runPython method with QProcess, although it is functioning now
int QTPython::runPython(const char* file_path){
    QString program = pypath.c_str();
    cout << pypath << " " << file_path << endl;
    QStringList arguments;
    arguments << file_path;

    if(py_status){
        killpy();
    }

    py_process->start(program, arguments);
    py_status = 1;
    py_process->waitForFinished(-1);

    return py_status;
}

// TODO: more
int QTPython::runPythonAsync(QString file_path){
    QString program = pypath.c_str();
    cout << pypath << " " << file_path.toStdString() << endl;
    QStringList arguments;
    arguments << "-u";
    arguments << file_path;
    string outputs, tmp;
    outputs = "";

    py_process->start(program, arguments);
    py_process->waitForStarted(-1);
    py_status = 1;
    cout << "training started" << endl;
    while(py_process->state() != QProcess::ProcessState::NotRunning && py_status)
    {
        qApp->processEvents();
        tmp = py_process->readAllStandardOutput().toStdString();
        if(tmp != outputs){
            outputs = tmp;
            cout << outputs << endl;
            emit outputUpdated(outputs);
        }
    }
    cout << "Terminating Python" << endl;
    py_process->terminate();
    py_process->kill();
    py_process->terminate();
    py_process->waitForFinished(-1);
    return py_status;
}

void QTPython::killtb()
{
    tb_status = 0;
    tb_process->waitForFinished(-1);
}

void QTPython::killpy()
{
    py_status = 0;
    py_process->waitForFinished(-1);
}

// TODO: activateTB method with QProcess
int QTPython::activateTB(const char* log_dir){
    cout << log_dir << endl;

    QString program = tbpath.c_str();
    QStringList arguments;
    arguments << "--logdir" << log_dir;

    tb_process->start(program, arguments);
    tb_process->waitForStarted();

    tb_status = 1;

    QDesktopServices::openUrl(QUrl("http://localhost:6006/"));
    cout << "TB started" << endl;
    while(tb_process->state() != QProcess::ProcessState::NotRunning && tb_status)
    {
        qApp->processEvents();
    }
    cout << "Terminating Tensorboard" << endl;
    tb_process->terminate();
    tb_process->kill();
    tb_process->terminate();
    tb_process->waitForFinished(-1);
    cout << "TB finished" << endl;
    return 1;
}
