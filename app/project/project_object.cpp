#include "project_object.h"

using namespace project;

project_object::project_object(QString name, Backend back):
    backend(back), graph_mdl(new GraphModel(back))
{
    // create a new project
    project_name = name;
    pro_desc_path = name + ".project";
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
