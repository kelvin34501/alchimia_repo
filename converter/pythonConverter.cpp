#include <iostream>
#include <string>
#include <map>

#include "converter.h"

using namespace std;

void PythonConverter::newfile(){
    pyfile = "";
    cur_indent = 0;
    empty_indent = false;
}

void PythonConverter::unindent(){
    if(cur_indent >= 0){
        --cur_indent;
        empty_indent = false;
    }
}

void PythonConverter::indent(){
    if(!empty_indent){
        ++cur_indent;
        empty_indent = true;
    }
}

void PythonConverter::addline(string statement){
    if(statement != ""){
        pyfile.append(cur_indent, '\t');
        pyfile.append(statement);
        empty_indent = false;
    }
    pyfile.append("\n");
}

void PythonConverter::addline(int lines){
    pyfile.append(lines, '\n');
}

void PythonConverter::def_state(string func_name, string params){
    addline(string("def ") + func_name + "(" + params + "):");
    indent();
}

void PythonConverter::def_state(string func_name, map<string, string> params){
    string ps = "";
    for(map<string, string>::iterator iter = params.begin(); iter != params.end(); iter++){
        if(iter->second == "")
            ps = iter->first + ", " + ps;
        else
            ps.append(", " + iter->first + "=" + iter->second);
    }
    def_state(func_name, ps);
}

void PythonConverter::import_state(string lib, string as, string from){
    addline(((from == "")?(""):("from " + from + " ")) + "import " + lib + ((as == "")?(""):(" as " + as)));
}

void PythonConverter::if_state(string cond){
    addline("if " + cond + ":");
    indent();
}

void PythonConverter::if_main_state(){
    front();
    if_state("__name__ == '__main__'");
}

void PythonConverter::with_state(string state, string alias){
    addline("with " + state + " as " + alias + ":");
    indent();
}

string PythonConverter::to_param_list(map<string, string> params){
    string res = "";
    for(map<string, string>::iterator iter=params.begin(); iter!=params.end(); iter++){
        if(iter->second != ""){
            res.append(iter->first + "=" + iter->second + ",");
        }
    }
    return res;
}


string PythonConverter::test_base_converter(){
    newfile();
    import_state("numpy", "np");

    addline(2);
    def_state("foo", "a");
    addline("print(a)");
    unindent();

    addline(2);
    if_state("__name__ == '__main__'");
    addline("b = np.array([1, 2])");
    addline("foo(b)");
    unindent();

    addline();
    return pyfile;
}
