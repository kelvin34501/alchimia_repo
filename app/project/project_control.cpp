#include "project_control.h"
#include "projectsettingdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace project;
using namespace std;

int project_control::active()
{
    return active_project_id;
}

int project_control::add_new_project(QString name, Backend be, const QString &location)
{
    int cur_id = p.size();
    p.push_back(make_shared<project_object>(name, be, location));
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

void project_control::save_project(int id)
{
    ofstream out(p[id]->pro_desc_path.toStdString(), ios::trunc);
    cereal::JSONOutputArchive ar(out);
    ar(*p[id]);
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

void project_control::create_new_project()
{
    ProjectSettingDialog project_setting_dialog(&main_window);
    if (project_setting_dialog.exec() == QDialog::Rejected)
        return;
    active_project_id = add_new_project(project_setting_dialog.projecName(),
                                        project_setting_dialog.backend(),
                                        project_setting_dialog.projectPath());

    QDir d(project_setting_dialog.projectPath());
    d.mkdir(project_setting_dialog.projecName());

    shared_ptr<project_object> p = (*this)[active_project_id];

    ModelControl *modelControl = new ModelControl(p);
    main_window.setModelControl(modelControl);
    connect(main_window_ui.actionCompile, SIGNAL(triggered()),
            modelControl, SLOT(compileModel()));

    ModelScene *modelScene = new ModelScene(*main_window_ui.toolBoxButtonGroup,
                                            *p, *main_window_ui.connectButton);
    main_window.setModelScene(modelScene);
    main_window_ui.graphicsView->setScene(modelScene);
    main_window_ui.graphicsView->setEnabled(true);
}
