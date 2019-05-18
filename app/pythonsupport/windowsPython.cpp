#include "pythonadapter.h"
#include <iostream>
#include <Windows.h>
#include <cstring>

using namespace std;

int WindowsPython::runPython(const char* file_path){
    LPTSTR sConLin = (LPTSTR)(("\"" + pypath + "\" \"" + file_path + "\"").c_str());
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
    bool flag;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

    Sleep(500);

    if(CreateProcess(NULL, sConLin, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	{
		cout << "create process success" << endl;
        WaitForSingleObject(pi.hProcess, INFINITE);
        flag = 1;
	}
	else{
		cerr << "failed to create process" << endl;
        flag = 0;
	}

    Sleep(500);

	TerminateProcess(pi.hProcess, 300);

    return flag;
}

int WindowsPython::activateTB(const char* log_dir){
    LPTSTR sConLin = (LPTSTR)(("\"" + tbpath + "\" \"" + log_dir + "\"").c_str());
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
    bool flag;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

    Sleep(500);

    if(CreateProcess(NULL, sConLin, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	{
		cout << "create process success" << endl;
        WaitForSingleObject(pi.hProcess, INFINITE);
        flag = 1;
	}
	else{
		cerr << "failed to create process" << endl;
        flag = 0;
	}

    Sleep(500);

	TerminateProcess(pi.hProcess, 300);

    return flag;
}

void WindowsPython::setPythonPath(const char* path){
    pypath = path;
}

void WindowsPython::setTBPath(const char* path){
    tbpath = path;
}
