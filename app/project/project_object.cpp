#include "project_object.h"
#include <QDebug>

using namespace project;

project_object::project_object(QString name, Backend back, QString location):
    backend(back), graph_mdl(new GraphModel(back))
{
    // create a new project
    project_name = name;
    pro_desc_path = name + ".project";
    if (location.back() != '/')
        location.append('/');
    QByteArray project_base_path((location + name + '/').toUtf8());
    compile_cfg.archi_path = string(project_base_path.constData()) + "architecture.json";
    compile_cfg.pyfile_path = string(project_base_path.constData()) + "model.py";
}

void project_object::gen()
{
    ofstream out(compile_cfg.pyfile_path, std::ios::trunc);
    out << graph_mdl->getPythonFileModel(compile_cfg) << std::endl;
    out.close();
}

void project_object::gen_train()
{
    ofstream out(compile_cfg.pyfile_path, std::ios::trunc);
    out << graph_mdl->getPythonFileTrain(train_cfg) << std::endl;
    out.close();
}

void project_object::gen_test()
{
    ofstream out(compile_cfg.pyfile_path, std::ios::trunc);
    out << graph_mdl->getPythonFileTest(test_cfg) << std::endl;
    out.close();
}
