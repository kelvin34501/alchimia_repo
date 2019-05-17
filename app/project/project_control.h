#ifndef PROJECT_CONTROL_H
#define PROJECT_CONTROL_H

#include "project_object.h"
#include "converter/converter.h"
#include "cereal/archives/json.hpp"
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <vector>
#include <memory>

namespace project {

class project_control
{
private:
    std::vector<std::shared_ptr<project_object>> p;
    int active_project_id;
public:
    explicit project_control();
    project_control(const project_control &other) = delete;
    project_control& operator=(const project_control &other) = delete;
    ~project_control() = default;

    int active();
    int add_new_project(QString name, Backend be);
    int add_existing_project(QString path);
    shared_ptr<project_object> operator[](int id);
    const shared_ptr<project_object> operator[](int id) const;
    void save_project(int id);
    void close_project(int id);
};

}


#endif // PROJECT_CONTROL_H
