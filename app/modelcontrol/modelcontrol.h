#ifndef MODELCONTROL_H_INCLUDED
#define MODELCONTROL_H_INCLUDED

#include <iostream>
#include <QObject>
#include "../pythonsupport/pythonadapter.h"
#include "../utils/configurations.h"
#include "../graphmodel/graphmodel.h"
#include "project/project_object.h"

using namespace std;
using namespace project;

class ModelControl : public QObject {
    Q_OBJECT

public:
    ModelControl(shared_ptr<project_object> p, PythonAdapter* python=nullptr, const char* pypath="", const char* tbpath="")
        : project(p) {
        this->python = python;
        if(this->python != nullptr){
            this->python->setPythonPath(pypath);
            this->python->setTBPath(tbpath);
        }
    };
    ~ModelControl(){
        delete this->python;
    }
    /* configureCompilation: starts compilation after configured in        */
    /*      CompileConfigurationWindow                                     */
    /* param:
        compile_cfg: CompileCFG, the configuration passed from CompileConfigurationWindow.
                Details of CompileCFG are in configurations.h.
    */
    void configureCompilation(CompileCFG compile_cfg);
    /* setPython: set or update python adapter, the original python adapter */
    /*          will be deleted                                             */
    void setPython(PythonAdapter* python) {
        if(this->python != nullptr){
            delete this->python;
        }
        this->python = python;
    }
    // /* setGraphModel: set or update graph model */
    // void setGraphModel(GraphModel* gm) { this->gm = gm; }
private slots:
    /**
    * Initiate use case,  create CompileConfigurationWindow.
    * SHOULD CHECK whether python adapter and graph model are set.
    * Connected to actionCompile's triggered().
    */
    void compileModel();
private:
    /* launchCompile: start the real compilation, including python */
    /*      generation and running python file                     */
    void launchCompile(CompileCFG compile_cfg);
    PythonAdapter* python;
    shared_ptr<project_object> project;
};

#endif // MODELCONTROL_H_INCLUDED
