#include <iostream>
#include <Windows.h>
#include <cstring>

using namespace std;

int main(){
    string pypath = "D:\\Anaconda3\\python.exe";
    cout << "enter runPython \n";
//    LPTSTR sConLin = (LPTSTR)(("\"" + pypath + "\" \"" + file_path + "\"").c_str());
    LPTSTR sConLin = (LPTSTR)(("\"" + pypath + "\" \"" + "D:\\Bruce\\Courses\\a\\architecture.gen" + "\"").c_str());
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
    bool flag;

//    cout << ("\"" + pypath + "\" \"" + file_path + "\"").c_str() << endl;
    cout << ("\"" + pypath + "\" \"" + "D:\\Bruce\\Courses\\a\\architecture.gen" + "\"").c_str() << endl;

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

    return 0;
}