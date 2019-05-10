#ifndef CONVERTER_H_INCLUDED
#define CONVERTER_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

#include "graphmodel_name.h"
// #include "namedef.h"

using namespace std;

/* Backend for converter to select */
enum Backend{
    Keras,
    Pytorch
};

/* Base python converter */
/* Support basic python statement template */
class PythonConverter{
public:
    virtual string getPythonFileModel(const GraphModel &gm) = 0;
    virtual string getPythonFileTrain(const GraphModel &gm) = 0;
    virtual string getPythonFileTest(const GraphModel &gm) = 0;
    virtual ~PythonConverter() {};
    string test_base_converter();
protected:
    string pyfile;  // the python file
    void newfile();  // reset file state
    void unindent();
    void indent();
    void addline(string statement="");
    void addline(int lines);  // add empty lines
    void def_state(string func_name, string params="");  // function define
    void def_state(string func_name, map<string, string> params);  // function define
    void import_state(string lib, string as="", string from="");  // import statement
    void if_state(string cond);  // if head
    void if_main_state();  // main if
    string to_param_list(map<string, string> params);  // convert param map to param string
    void front() { cur_indent = 0; };  // set indent to 0
    virtual void group_import() = 0;  // import template for different backend
private:
    int cur_indent;
    bool empty_indent;  // to avoid continuous empty indent
};

/* Converter supporting Keras backend */
class KerasConverter : public PythonConverter{
public:
    string getPythonFileModel(const GraphModel &gm);
    string getPythonFileTrain(const GraphModel &gm);
    string getPythonFileTest(const GraphModel &gm);
    ~KerasConverter() {};
protected:
    void group_import();
    void add_layer(PartType parttype, map<string, string> params, string model="model");
private:
};

# endif // CONVERTER_H_INCLUDED
