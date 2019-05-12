#ifndef PROJECT_H
#define PROJECT_H

#include <random>
#include <memory>
#include <vector>
using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;

#include <QString>
#include <QDir>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>

#include <graphmodel/graphmodel.h>
#include <converter/converter.h>

#include <project/sereialize.hpp>

namespace project {

static const int MAX_TRY = 4000;

class project_object
{
private:
    QString project_name;

    QString pro_desc_path; // project file (stores graph structure)
    QString mdl_py_path; // model python file
    QString mdl_desc_path; // model json file
    QString mdl_py_code; // model python code

    Backend backend; // backend information
    unique_ptr<GraphModel> graph_mdl; // graph model
public:
    explicit project_object(QString name); // open project
    explicit project_object(QString name, Backend back); // create project
    project_object(const project_object &o); // copy con
    project_object& operator=(const project_object &o); // override =
    ~project_object(); // save, close project

    void save();
    void load();
};

}
#endif // PROJECT_H
