#include <iostream>
#include <string>
#include <fstream>
#include "modelcontrol.h"

using namespace std;

void ModelControl::compileModel(){
    configureCompilation(pc->get_active_project()->compile_cfg);
}

void ModelControl::configureCompilation(CompileCFG compile_cfg){
    // generate python file path based on architecture path set by user
    compile_cfg.pyfile_path = compile_cfg.archi_path.substr(0, compile_cfg.archi_path.size()-4) + "gen";

    // TODO: save project and do other adjustment
    pc->save_active_project();

    // launch compile
    launchCompile(compile_cfg);
}

void ModelControl::launchCompile(CompileCFG compile_cfg){
    // get python file
    shared_ptr<project_object> project = pc->get_active_project();
    ofstream outfile(compile_cfg.pyfile_path);
    if(!outfile.is_open()){
        cout << "error saving files" << endl;
        return;
    }
    else{
        outfile << project->graph_mdl->getPythonFileModel(compile_cfg);
    }
    outfile.close();

    // run python file
    if(python->runPython(compile_cfg.pyfile_path.c_str())){
        project->graph_mdl->model_cfg.archi_path = compile_cfg.archi_path;
    }
}
