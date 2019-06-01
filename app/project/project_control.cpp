#include "project_control.h"
#include "projectsettingdialog.h"
#include "popoutnotification.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace project;
using namespace std;

void project_control::post_project_creation()
{
    // create and set up model control
    // TODO: dummy python adapter, should be chosen based on situations
    PythonAdapter *pyad = new QTPython ();
    ModelControl *modelControl = new ModelControl(main_window, this, pyad);
    main_window.setModelControl(modelControl);
    connect(main_window_ui.actionCompile, SIGNAL(triggered()),
            modelControl, SLOT(compileModel()));

    // create and set up editor control (model scene)
    shared_ptr<project_object> p = (*this)[active_project_id];
    ModelScene *modelScene = new ModelScene(*main_window_ui.toolBoxButtonGroup, *p);

    // update main panel
    main_window.setModelScene(modelScene);
    main_window_ui.graphicsView->setScene(modelScene);
    main_window_ui.graphicsView->setEnabled(true);
    main_window_ui.actionSave_Project->setEnabled(true);
}

int project_control::active()
{
    return active_project_id;
}

int project_control::add_new_project(QString name, Backend be, const QString &location, QString pypath, QString tbpath)
{
    int cur_id = p.size();
    p.push_back(make_shared<project_object>(name, be, location, pypath, tbpath));
    return cur_id;
}

int project_control::add_existing_project(QString path)
{
    int cur_id = p.size();
    p.push_back(make_shared<project_object>());
    ifstream in(path.toStdString());
    cereal::JSONInputArchive ar(in);
    ar(*p[cur_id]);
    return cur_id;
}

void project_control::save_project(size_type id)
{
//    PopoutNotification notification(&main_window);
//    notification.hideButton();
//    notification.updateMessage("Saving Project...");
    ofstream out(p[id]->project_cfg.pro_desc_path.toStdString(), ios::trunc);
    cereal::JSONOutputArchive ar(out);
    ar(*p[id]);
//    notification.close();
}

void project_control::save_active_project()
{
    save_project(active_project_id);
}

void project_control::close_project(int id)
{
    save_project(id);
    p[id] = nullptr;
}

shared_ptr<project_object> project_control::operator[](int id)
{
    return shared_ptr<project_object>(p[id]);
}

const shared_ptr<project_object> project_control::operator[](int id) const
{
    return shared_ptr<project_object>(p[id]);
}

shared_ptr<project_object> project_control::get_active_project(){
    return (*this)[active_project_id];
}

void project_control::create_new_project()
{
    // create a project setting dialog
    ProjectSettingDialog project_setting_dialog(&main_window);
    if (project_setting_dialog.exec() == QDialog::Rejected)
        return;
    
    // create a new project with data from the project setting dialog
    active_project_id = add_new_project(project_setting_dialog.projecName(),
                                        project_setting_dialog.backend(),
                                        project_setting_dialog.projectPath(),
                                        project_setting_dialog.pythonPath(),
                                        project_setting_dialog.tensorboardPath());

    // update system directory
    QDir d(project_setting_dialog.projectPath());
    d.mkdir(project_setting_dialog.projecName());

    post_project_creation();
}
