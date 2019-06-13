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

class ModelControl;

void test(ModelControl* mc, const char* a);

class ModelControl : public QObject {
    Q_OBJECT

public:
    ModelControl(MainWindow &mw, project_control *pc, PythonAdapter* python = nullptr);
    ~ModelControl(){
        python->killtb();
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
    void setModelConfiguration(ModelCFG model_cfg);
    void setDataConfiguration(DataCFG data_cfg);
    bool modelSet();
    bool dataSet();
    void compileModelPublic() { compileModel(); }
    void configureModelPublic() { configureModel(); }
    void configureDataPublic() { configureData(); }
    ModelCFG getCurrentModelCFG() {
        return pc->get_active_project()->graph_mdl->model_cfg;
    }
    DataCFG getCurrentDataCFG() {
        return pc->get_active_project()->graph_mdl->data_cfg;
    }
private slots:
    /**
    * Initiate use case,  create CompileConfigurationWindow.
    * SHOULD CHECK whether python adapter and graph model are set.
    * Connected to actionCompile's triggered().
    */
    void compileModel();
    void trainModel();
    void configureModel();
    void configureData();
    void TBVisualization();
private:
    /* launchCompile: start the real compilation, including python */
    /*      generation and running python file                     */
    void launchCompile(CompileCFG compile_cfg);
    void launchTraining(TrainCFG train_cfg);
    void launchTB(string logdir);
    PythonAdapter* python;
//    shared_ptr<project_object> project;
    project_control *pc;
    MainWindow &main_window;
    friend void test(ModelControl* mc, const char* a);
};

#endif // MODELCONTROL_H_INCLUDED
