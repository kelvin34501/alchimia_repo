#include <iostream>
#include <string>
#include <fstream>
#include "modelcontrol.h"
#include "compileconfigurationdialog.h"
#include "popoutnotification.h"
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
    PopoutNotification notification(&main_window);
    notification.hideButton();
    notification.updateMessage("Configuring Workspace...");

    // configure workspace
    QDir dir;
    string workspace = pc->get_active_project()->workspace();
    dir.mkpath(QString::fromStdString(workspace + compile_cfg.archi_name));
    compile_cfg.archi_path = workspace + compile_cfg.archi_path;
    compile_cfg.pyfile_path = workspace + compile_cfg.pyfile_path;
    cout << compile_cfg.pyfile_path << endl;

//    notification.updateMessage("Generating Python File...");

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

//    notification.updateMessage("Compiling Model...");

    // run python file
    if(python->runPython(compile_cfg.pyfile_path.c_str())){
        project->graph_mdl->model_cfg.archi_path = compile_cfg.archi_path;
    }

    notification.updateMessage("Compilation Complete.");
    notification.showButton();
    notification.exec();
}

void ModelControl::configureTraining(TrainCFG train_cfg)
{
    launchTraining(train_cfg);
}

void ModelControl::launchTraining(TrainCFG train_cfg)
{
    // get python file
    shared_ptr<project_object> project = pc->get_active_project();
    ofstream outfile(train_cfg.save_weight_dir + "/" + train_cfg.model_name + "_train.gen");
    if (!outfile.is_open())
    {
        cout << "error saving files" << endl;
        return;
    }
    else
    {
        outfile << project->graph_mdl->getPythonFileTrain(train_cfg);
    }
    outfile.close();

    // TODO: run python
}

// TODO: setArchitecturePath might need other changes
void ModelControl::setModelPath(ModelCFG model_cfg){
    pc->get_active_project()->graph_mdl->model_cfg = model_cfg;
}

// TODO: setDataConfiguration might need other changes
void ModelControl::setDataConfiguration(DataCFG data_cfg){
    pc->get_active_project()->graph_mdl->data_cfg = data_cfg;
}
