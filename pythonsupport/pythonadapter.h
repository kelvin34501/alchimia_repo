#ifndef PYTHONADAPTER_H_INCLUDED
#define PYTHONADAPTER_H_INCLUDED

#include <iostream>

using namespace std;

class PythonAdapter{
public:
    virtual int runPython(const char* file_path) = 0;
    virtual int activateTB(const char* log_dir) = 0;
    virtual ~PythonAdapter() {};
};

#endif // PYTHONADAPTER_H_INCLUDED
