#include <iostream>
#include <string>
#include <fstream>
#include "modelcontrol.h"
#include "compileconfigurationdialog.h"
#include "modelconfigurationdialog.h"
#include "dataconfigurationdialog.h"
#include "tbvisuaizationdialog.h"
#include "trainconfigurationdialog.h"
#include "popoutnotification.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QtConcurrent>
#include <QMessageBox>

using namespace std;

ModelControl::ModelControl(MainWindow &mw, Ui::MainWindow &mwui, project_control *pc,
                           PythonAdapter* python) : main_window(mw), main_window_ui(mwui)
{
    this->python = python;
    this->pc = pc;
    if (this->python) {
        const ProjectCFG &config = pc->get_active_project()->project_cfg;
        this->python->setPythonPath(config.python_path.toUtf8());
        this->python->setTBPath(config.tensorboard_path.toUtf8());
    }
    cache_train_cfg.metrics.push_back("acc");
}

bool ModelControl::modelSet(){
    ModelCFG cfg = pc->get_active_project()->graph_mdl->model_cfg;
    return cfg.archi_path != "";
}

bool ModelControl::dataSet(){
    DataCFG cfg = pc->get_active_project()->graph_mdl->data_cfg;
    return cfg.dataset != "";
}

void ModelControl::interrupt(){
    python->killpy();
    python->killtb();
}

#pragma region compile

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

#pragma endregion compile

#pragma region train

void ModelControl::trainModel()
{
    TrainCFG train_cfg;
    bool flag;

    train_cfg = cache_train_cfg;

    // TODO: remove following default settings
    train_cfg.model_name = "test_model";
    train_cfg.save_weight_dir = "D:/a/weights";
    train_cfg.tb_cfg.log_dir = "D:/a/logs";

    do
    {
        TrainConfigurationDialog train_cfg_dialog(train_cfg, &main_window, this);
        if (train_cfg_dialog.exec() == QDialog::Rejected)
            return;
        train_cfg = train_cfg_dialog.TrainConfiguration();
        flag = (train_cfg.model_name == "" || train_cfg.save_weight_dir == ""
                || train_cfg.metrics.size() <= 0);
    } while (flag);
    cout << "cache cfg" << endl;
    cache_train_cfg = train_cfg;

    configureTraining(train_cfg);
}

void ModelControl::configureTraining(TrainCFG train_cfg)
{
    while(!modelSet()){
        QMessageBox msgBox;
        msgBox.setText("Model has not configured yet!");
        msgBox.setInformativeText("Do you want to configure model and continue training?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes){
            configureModel();
        }
        else{
            return;
        }
    }

    while(!dataSet()){
        QMessageBox msgBox;
        msgBox.setText("Data has not configured yet!");
        msgBox.setInformativeText("Do you want to configure data and continue training?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes){
            configureData();
        }
        else{
            return;
        }
    }

    launchTraining(train_cfg);
}

void ModelControl::launchTraining(TrainCFG train_cfg)
{
    QMessageBox msgBox;
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

    main_window_ui.actionTrain->setEnabled(false);
    main_window_ui.actionCompile->setEnabled(false);
    main_window_ui.actionRunTest->setEnabled(false);

    QtConcurrent::run(this, &ModelControl::launchTB, train_cfg.tb_cfg.log_dir);
//    QFuture<int> future = QtConcurrent::run(python, &PythonAdapter::runPythonAsync, QString::fromStdString(train_cfg.save_weight_dir + "/" + train_cfg.model_name + "_train.gen"));
    int res = python->runPythonAsync(QString::fromStdString(train_cfg.save_weight_dir + "/" + train_cfg.model_name + "_train.gen"));

//    if(future.result()){
   if(res){
        project->graph_mdl->model_cfg.weight_path = train_cfg.save_weight_dir + train_cfg.model_name + ".h5";
        msgBox.setText("Training complete.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

   main_window_ui.actionTrain->setEnabled(true);
   main_window_ui.actionCompile->setEnabled(true);
   main_window_ui.actionRunTest->setEnabled(true);
}

#pragma endregion train

#pragma region cfgModel

void ModelControl::configureModel()
{
    ModelConfigurationDialog model_cfg_dialog(pc->get_active_project()->graph_mdl->model_cfg, &main_window);
    if (model_cfg_dialog.exec() == QDialog::Rejected)
        return;
    setModelConfiguration({model_cfg_dialog.archiPath().toStdString(),
                           model_cfg_dialog.weightPath().toStdString()});
}

// TODO: setArchitecturePath might need other changes
void ModelControl::setModelConfiguration(ModelCFG model_cfg){
    pc->get_active_project()->graph_mdl->model_cfg = model_cfg;
}

#pragma endregion cfgModel

#pragma region cfgData

void ModelControl::configureData()
{
    DataConfigurationDialog data_cfg_dialog(pc->get_active_project()->graph_mdl->data_cfg, &main_window, pc);
    connect(&data_cfg_dialog, SIGNAL(modelUpdated()),
            main_window.modelScene(), SLOT(updateInfoDisplay()));
    DataCFG data_cfg;
    if (data_cfg_dialog.exec() == QDialog::Rejected)
        return;
    if(data_cfg_dialog.datasetName() == "<<None>>")
    {
        data_cfg.dataset = "";
    }
    else
    {
        data_cfg.dataset = data_cfg_dialog.datasetName().toStdString();
    }

    setDataConfiguration(data_cfg);
}

// TODO: setDataConfiguration might need other changes
void ModelControl::setDataConfiguration(DataCFG data_cfg){
    pc->get_active_project()->graph_mdl->data_cfg = data_cfg;
}

#pragma endregion cfgData

#pragma region tbvisual

void test(ModelControl* mc, const char* a)
{
    mc->python->activateTB(a);
}

void ModelControl::TBVisualization(){
    TBVisuaizationDialog tb_dialog(&main_window, this);
    if (tb_dialog.exec() == QDialog::Rejected)
        return;
//    QtConcurrent::run(test, this, tb_dialog.logDir().toStdString().data());
    python->killtb();
    python->activateTB(tb_dialog.logDir().toStdString().data());
}

void ModelControl::launchTB(string logdir){
    python->killtb();
    python->activateTB(logdir.data());
}

#pragma endregion tbvisual

