#ifndef CONVERTER_H_INCLUDED
#define CONVERTER_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

#include "../graphmodel/graphmodel_name.h"
#include "../utils/configurations.h"
#include "../utils/enum_cast.hpp"
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
    virtual string getPythonFileModel(const GraphModel &gm, CompileCFG cfg) = 0;
    virtual string getPythonFileTrain(const GraphModel &gm, TrainCFG cfg) = 0;
    virtual string getPythonFileTest(const GraphModel &gm, TestCFG cfg) = 0;
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
    void with_state(string state, string alias);  // with as
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
    string getPythonFileModel(const GraphModel &gm, CompileCFG cfg);
    string getPythonFileTrain(const GraphModel &gm, TrainCFG cfg);
    string getPythonFileTest(const GraphModel &gm, TestCFG cfg);
    ~KerasConverter() {};
protected:
    void group_import();
private:
    void add_layer(PartType parttype, map<string, string> params, string model="model");
    string parse_compile_param(TrainCFG train_cfg) const;
    string parse_fit_param(DataCFG data_cfg, TrainCFG train_cfg) const;
    string parse_tb_param(TBCFG tb_cfg) const;
};

# endif // CONVERTER_H_INCLUDED
