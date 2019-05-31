#include "project_object.h"
#include <QDebug>

using namespace project;

project_object::project_object(QString name, Backend back, QString location, QString pypath, QString tbpath):
    backend(back), graph_mdl(new GraphModel(back))
{
    // create a new project
    project_cfg.name = name;
    if (location.back() != '/')
        location.append('/');
    project_cfg.location = location;
    QString project_base_path = location + name + '/';
    project_cfg.pro_desc_path = project_base_path + name + ".project";
    project_cfg.python_path = pypath;
    project_cfg.tensorboard_path = tbpath;
}
