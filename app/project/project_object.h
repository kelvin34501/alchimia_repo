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
#include <fstream>

#include <graphmodel/graphmodel.h>
#include <converter/converter.h>
#include <utils/configurations.h>

#include <project/sereialize.hpp>

namespace project {

static const int MAX_TRY = 4000;

class project_object
{
public:
    ProjectCFG project_cfg;
    CompileCFG compile_cfg;
    TrainCFG train_cfg;
    TestCFG test_cfg;

    Backend backend; // backend information
    unique_ptr<GraphModel> graph_mdl; // graph model

    explicit project_object() {}
    explicit project_object(QString name, Backend back, QString location, QString pypath, QString tbpath); // create project
    project_object(const project_object &o) = delete; // copy con
    project_object& operator=(const project_object &o) = delete; // override =
    ~project_object() {}
    string workspace() const { return (project_cfg.location + project_cfg.name + "/").toStdString(); }

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(cereal::make_nvp("backend", backend),
           cereal::make_nvp("model", graph_mdl),
           cereal::make_nvp("project_cfg", project_cfg),
           cereal::make_nvp("compile_cfg", compile_cfg),
           cereal::make_nvp("train_cfg", train_cfg),
           cereal::make_nvp("test_cfg", test_cfg));
    }
};

}
#endif // PROJECT_H
