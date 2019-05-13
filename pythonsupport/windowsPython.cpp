#include "pythonadapter.h"
#include <iostream>
#include<Windows.h>

using namespace std;

int WindowsPython::runPython(const char* file_path){
    LPTSTR sConLin = (pypath + " \"" + file_path + "\"").c_str;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
 
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

    if(CreateProcess(NULL, sConLin, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	{
		cout << "create process success" << endl;
        WaitForSingleObject(pi.hProcess, INFINITE);
	}
	else{
		cerr << "failed to create process" << endl;
	}

	TerminateProcess(pi.hProcess, 300);
}

int WindowsPython::activateTB(const char* log_dir){

}

void WindowsPython::setPythonPath(const char* path){
    pypath = path;
}
