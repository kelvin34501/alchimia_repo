#include <iostream>
#include <string>
#include <fstream>
#include "modelcontrol_d.h"

using namespace std;

void ModelControl::configureCompilation(CompileCFG compile_cfg)
{
    // generate python file path based on architecture path set by user
    compile_cfg.pyfile_path = compile_cfg.archi_path.substr(0, compile_cfg.archi_path.size() - 4) + "gen";

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
    if (python->runPython(compile_cfg.pyfile_path.c_str()))
    {
        gm->model_cfg.archi_path = compile_cfg.archi_path;
    }
}

void ModelControl::configureTraining(TrainCFG train_cfg)
{
    train_cfg.metrics.push_back("accuracy");

    launchTraining(train_cfg);
}

void ModelControl::launchTraining(TrainCFG train_cfg)
{
    // get python file
    ofstream outfile(train_cfg.save_weight_path + "/" + train_cfg.model_name + "_train.gen");
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
}
