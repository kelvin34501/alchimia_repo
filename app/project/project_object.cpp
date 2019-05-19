#include "project_object.h"
#include <QDebug>

using namespace project;

project_object::project_object(QString name, Backend back, QString location):
    backend(back), graph_mdl(new GraphModel(back))
{
    // create a new project
    project_name = name;
    if (location.back() != '/')
        location.append('/');
    project_location = location;
    QByteArray project_base_path((location + name + '/').toUtf8());
    pro_desc_path = project_base_path.constData() + name + ".project";
    compile_cfg.archi_path = string(project_base_path.constData()) + "architecture.json";
    compile_cfg.pyfile_path = string(project_base_path.constData()) + "model.py";
}
