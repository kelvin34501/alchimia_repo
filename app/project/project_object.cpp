#include "project_object.h"

using namespace project;

project_object::project_object(QString name)
{
    // loads an existing project
}

project_object::project_object(QString name, Backend back):
    backend(back), graph_mdl(new GraphModel(back))
{
    // create a new project
    project_name = name;
    pro_desc_path = name + ".project";
    mdl_py_path = name + ".gen";
    mdl_desc_path = name + ".json";
}

project_object::~project_object()
{

}

void project_object::save()
{

}

void project_object::load()
{

}
