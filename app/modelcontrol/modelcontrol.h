#ifndef MODELCONTROL_H_INCLUDED
#define MODELCONTROL_H_INCLUDED

#include <iostream>
#include <QObject>
#include "../pythonsupport/pythonadapter.h"
#include "../utils/configurations.h"
#include "../graphmodel/graphmodel.h"
#include "project/project_object.h"
#include "project/project_control.h"

using namespace std;
using namespace project;

class ModelControl : public QObject {
    Q_OBJECT

public:
    ModelControl(MainWindow &mw, project_control *pc, PythonAdapter* python = nullptr);
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
    // void setGraphModel(GraphModel *gm) { this->gm = gm; }
    void configureTraining(TrainCFG train_cfg);
    void setModelPath(ModelCFG model_cfg);
    void setDataConfiguration(DataCFG data_cfg);
private slots:
    /**
    * Initiate use case,  create CompileConfigurationWindow.
    * SHOULD CHECK whether python adapter and graph model are set.
    * Connected to actionCompile's triggered().
    */
    void compileModel();
    void trainModel() {}
    void loadArchitecture() {}
    void configureData() {}
private:
    /* launchCompile: start the real compilation, including python */
    /*      generation and running python file                     */
    void launchCompile(CompileCFG compile_cfg);
    void launchTraining(TrainCFG train_cfg);
    PythonAdapter* python;
//    shared_ptr<project_object> project;
    project_control *pc;
    MainWindow &main_window;
};

#endif // MODELCONTROL_H_INCLUDED
