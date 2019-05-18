#ifndef MODELCONTROL_D_H_INCLUDED
#define MODELCONTROL_D_H_INCLUDED

#include <iostream>
#include "../pythonsupport/pythonadapter.h"
#include "../utils/configurations.h"
#include "../graphmodel/graphmodel.h"

using namespace std;

class ModelControl{
public:
    ModelControl(PythonAdapter* python=nullptr){
        this->python = python;
        // this->gm = gm;
    };
    /* compileModel: initiate use case, create CompileConfigurationWindow. */
    /*      SHOULD CHECK whether python adapter and graph model are set.   */
    void compileModel();
    /* configureCompilation: starts compilation after configured in        */
    /*      CompileConfigurationWindow                                     */
    /* param:
        compile_cfg: CompileCFG, the configuration passed from CompileConfigurationWindow.
                Details of CompileCFG are in configurations.h.
    */
    void configureCompilation(CompileCFG compile_cfg);
    /* setPython: set or update python adapter */
    void setPython(PythonAdapter* python) { this->python = python; }
    // /* setGraphModel: set or update graph model */
    // void setGraphModel(GraphModel* gm) { this->gm = gm; }
private:
    /* launchCompile: start the real compilation, including python */
    /*      generation and running python file                     */
    void launchCompile(CompileCFG compile_cfg);
    PythonAdapter* python;
    // GraphModel* gm;
};

#endif // MODELCONTROL_D_H_INCLUDED
