#include <iostream>
#include <string>
#include <fstream>
#include "modelcontrol_d.h"

using namespace std;

void ModelControl::configureCompilation(CompileCFG compile_cfg)
{
    // generate python file path based on architecture path set by user
    compile_cfg.pyfile_path = compile_cfg.archi_path.substr(0, compile_cfg.archi_path.size() - 5) + "_compile.gen";

    // TODO: save project and do other adjustment

    // launch compile
    launchCompile(compile_cfg);
}

void ModelControl::launchCompile(CompileCFG compile_cfg)
{
    // get python file
    ofstream outfile(compile_cfg.pyfile_path);
    if (!outfile.is_open())
    {
        cout << "error saving files" << endl;
        return;
    }
    else
    {
        outfile << gm->getPythonFileModel(compile_cfg);
    }
    outfile.close();

    // run python file
    bool result = python->runPython(compile_cfg.pyfile_path.c_str());
    if (result)
    {
        gm->model_cfg.archi_path = compile_cfg.archi_path;
    }
}

void ModelControl::configureTraining(TrainCFG train_cfg)
{
    launchTraining(train_cfg);
}

void ModelControl::launchTraining(TrainCFG train_cfg)
{
    // get python file
    // '/' should be already attached to train_cfg.save_weight_dir
    ofstream outfile(train_cfg.save_weight_dir + train_cfg.model_name + "_train.gen");
    if (!outfile.is_open())
    {
        cout << "error saving files" << endl;
        return;
    }
    else
    {
        outfile << gm->getPythonFileTrain(train_cfg);
    }
    outfile.close();

    // TODO: run python
    if(python->runPython((train_cfg.save_weight_dir + train_cfg.model_name + "_train.gen").data())){
        gm->model_cfg.weight_path = train_cfg.save_weight_dir + train_cfg.model_name + ".h5";
    }
}

// TODO: setArchitecturePath might need other changes
void ModelControl::setModelPath(ModelCFG model_cfg){
    gm->model_cfg = model_cfg;
}

// TODO: setDataConfiguration might need other changes
void ModelControl::setDataConfiguration(DataCFG data_cfg){
    gm->data_cfg = data_cfg;
}
