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
//#include "modelcontrol/modelcontrol.h"

class MainWindow;

namespace Ui {
    class MainWindow;
}

namespace project {

class project_control : public QObject
{
    Q_OBJECT

private:
    std::vector<std::shared_ptr<project_object>> p;
    int active_project_id = -1;

    /**
    * @var Passed as a pointer to the dialogs.
    */
    MainWindow &main_window;

    /**
    * UI of mainwindow
    */
    Ui::MainWindow &main_window_ui;

    /**
    * This method is called after a Project is created. It is responsible for
    * binding Project to other classes.
    */
    void post_project_creation();
public:
    typedef std::vector<std::shared_ptr<project_object>>::size_type size_type;

    project_control(MainWindow &mw, Ui::MainWindow &mwui) noexcept;
    project_control(const project_control &other) = delete;
    project_control& operator=(const project_control &other) = delete;
    ~project_control() = default;

    int active();
    int add_new_project(QString name, Backend be, const QString &location, QString pypath, QString tbpath);
    int add_existing_project(QString path);
    shared_ptr<project_object> operator[](int id);
    const shared_ptr<project_object> operator[](int id) const;
    shared_ptr<project_object> get_active_project();
    void save_project(size_type id);
    void close_project(int id);

public slots:
    /**
    * Connected to the "New Project" button's clicked() signal
    */
    void create_new_project();
    void ConfigureSetting();

    /**
    * Connected to the "Save Project" button's clicked() signal
    */
    void save_active_project();
    void close_project();
    void open_project();

private:
    void set_pypath(QString pypath);
    void set_tbpath(QString tbpath);
};

}


#endif // PROJECT_CONTROL_H
