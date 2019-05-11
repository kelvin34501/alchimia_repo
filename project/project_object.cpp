#include "project_object.h"

using namespace project;

project_object::project_object(QString p, QString bkd)
{
    if (p.isEmpty()) {
        // p is empty, then generate a random name
        for (int i=0; i<4000; i++) {
            QString s = QString("%1.project").arg(i);
            QDir tmp_dir(s);
            if (!tmp_dir.exists()) {
                p = s;
                break;
            }
        }
    }

    QDir dir(p);
    if (!dir.exists()) {
        // create a project
        std::ofstream out;
        out.open(p.toStdString(), std::ios::trunc);

        cereal::JSONOutputArchive archive(out);
        archive(cereal::make_nvp("backend", bkd.toStdString()));

        vector<int> a;
        for (int j=0; j<100; j++)
            a.push_back(j);
        archive(cereal::make_nvp("aaa",a));
    }
}

project_object::~project_object()
{

}

void project_object::save()
{

}

void project_object::compile()
{

}

void project_object::run()
{

}
