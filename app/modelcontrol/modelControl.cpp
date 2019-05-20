#include <iostream>
#include <string>
#include <fstream>
#include "modelcontrol.h"
#include "compileconfigurationdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

using namespace std;

void ModelControl::compileModel(){
    CompileConfigurationDialog compile_cfg_dialog(&main_window);
    if (compile_cfg_dialog.exec() == QDialog::Rejected)
        return;
    configureCompilation({compile_cfg_dialog.archiName().toStdString(),
                         compile_cfg_dialog.genFile().toStdString(),
                         compile_cfg_dialog.pyFile().toStdString()});
}

void ModelControl::configureCompilation(CompileCFG compile_cfg){
    // save project
    pc->save_active_project();

    // launch compile
    launchCompile(compile_cfg);
}

void ModelControl::launchCompile(CompileCFG compile_cfg){
    // configure workspace
    QDir dir;
    string workspace = pc->get_active_project()->workspace();
    dir.mkpath(QString::fromStdString(workspace + compile_cfg.archi_name));
    compile_cfg.archi_path = workspace + compile_cfg.archi_path;
    compile_cfg.pyfile_path = workspace + compile_cfg.pyfile_path;
    cout << compile_cfg.pyfile_path << endl;

    // get and save python file
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
