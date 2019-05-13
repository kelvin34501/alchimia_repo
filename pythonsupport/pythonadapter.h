#ifndef PYTHONADAPTER_H_INCLUDED
#define PYTHONADAPTER_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class PythonAdapter{
public:
    virtual ~PythonAdapter() {};
    /* runPython: run the python at given path, does NOT wait or check status */
    /* param:
        file_path: string, the path of python file, extra "" will be auto added.
            The path is NOT selected by user, but generated by the ModelControl.
            MAY SWITCH TO INFORMATION IN QT.
    */
    virtual int runPython(const char* file_path) = 0;
    /* activateTB: activate Tensorboard and open browser */
    /* param:
        log_dir: string, the directory of Tensorboard log. The folder is created
            by the system, and the path is generated by the system. MAY SWITCH
            TO INFORMATION IN QT.
    */
    virtual int activateTB(const char* log_dir) = 0;
    /* setPythonPath: set path to the python.exe, should be called when creating */
    /*              or loading project                                           */
    /* param:
        path: string, the path to the python.exe, no "" will be auto added. The
            path IS selected by user. MAY SWITCH TO INFORMATION IN QT.
    */
    virtual void setPythonPath(const char* path) = 0;
};

/* Windows.h implementation of PythonAdapter */
class WindowsPython : public PythonAdapter{
public:
    ~WindowsPython() {};
    int runPython(const char* file_path);
    int activateTB(const char* log_dir);
    void setPythonPath(const char* path);
private:
    string pypath;
};

#endif // PYTHONADAPTER_H_INCLUDED
