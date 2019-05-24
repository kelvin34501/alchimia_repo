#include "pythonadapter.h"
#include <iostream>
#include <cstring>
#include <QtCore/QCoreApplication>
#include <QtCore/QProcess>
#include <QtCore/QStringList>

using namespace std;

// TODO: perfect the runPython method with QProcess, although it is functioning now
int QTPython::runPython(const char* file_path){
    QString program = pypath.c_str();
    cout << pypath << " " << file_path << endl;
    QStringList arguments;
    arguments << file_path;

    QProcess *process = new QProcess();
    process->start(program, arguments);
    process->waitForFinished();

    return 1;
}

// TODO: more
int QTPython::runPythonAsync(const char* file_path){
    QString program = pypath.c_str();
    cout << pypath << " " << file_path << endl;
    QStringList arguments;
    arguments << file_path;
    string outputs, tmp;
    outputs = "";

    QProcess *process = new QProcess();
    process->start(program, arguments);
    while(process->state() != QProcess::ProcessState::NotRunning)
    {
        qApp->processEvents();
        tmp = process->readAllStandardOutput().toStdString();
        cout << tmp << endl;
        if(tmp != outputs){
            outputs = tmp;
            cout << outputs << endl;
            emit outputUpdated(outputs);
        }
    }

    return 1;
}

// TODO: activateTB method with QProcess
int QTPython::activateTB(const char* log_dir){
    return 1;
}
