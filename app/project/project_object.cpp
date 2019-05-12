#include "project_object.h"

using namespace project;

#include <QDebug>

project_object::project_object(QString p, QString bkd)
{
    if (p.isEmpty()) {
        // p is empty, then generate a random name
        for (int i=0; i<4000; i++) {
            QString cur_path = QDir::currentPath();
            QString s = cur_path + QString("/%1.project").arg(i);
            QFileInfo tmp_file_info(s);
            qDebug() << tmp_file_info;
            qDebug() << tmp_file_info.exists();
            if (!tmp_file_info.exists()) {
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

        string sss = "fjkasfjkadsjf;adsj";
        archive(cereal::make_nvp("ssss",sss));
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
