#ifndef PYTHONADAPTER_H_INCLUDED
#define PYTHONADAPTER_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class PythonAdapter{
public:
    virtual ~PythonAdapter() {};
    virtual int runPython(const char* file_path) = 0;
    virtual int activateTB(const char* log_dir) = 0;
    virtual void setPythonPath(const char* path) = 0;
};

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
