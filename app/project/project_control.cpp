#include "project_control.h"

using namespace project;
using namespace std;

project_control::project_control()
{
    active_project_id = -1;
}

int project_control::active()
{
    return active_project_id;
}

int project_control::add_new_project(QString name, Backend be)
{
    int cur_id = p.size();
    p.push_back(make_shared<project_object>(name, be));
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

}

void project_control::close_project(int id)
{

}
