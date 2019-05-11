#ifndef PROJECT_H
#define PROJECT_H

#include <random>
#include <memory>
#include <vector>
using std::string;
using std::vector;

#include <QString>
#include <QDir>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

namespace converter {
// temp workaround and breaks system
// need to tell Wang Zhongye to move his code into namespaces
    #include <converter/graphmodel.h>
    #include <converter/converter.h>
}

#include <project/sereialize.h>

namespace project {

class project_object
{
private:
    QString pro_desc_path; // project file (stores graph structure)
    QString mdl_py_path; // model python file
    QString mdl_desc_path; // model json file
    QString mdl_py_code; // model python code

    enum converter::Backend backend; // backend information
    const converter::GraphModel *p_graph_mdl; // graph model
public:
    explicit project_object(QString p, QString b); // create/open project
    project_object(const project_object &o); // copy con
    project_object& operator=(const project_object &o); // override =
    ~project_object(); // save, close project

    void save();
    void compile();
    void run();
};

}
#endif // PROJECT_H
