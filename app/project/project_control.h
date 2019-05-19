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
    int active_project_id;

    /**
    * @var Passed as a pointer to the dialogs.
    */
    MainWindow &main_window;

    /**
    * UI of mainwindow
    */
    Ui::MainWindow &main_window_ui;
public:
    project_control(MainWindow &mw, Ui::MainWindow &mwui) noexcept
        : main_window(mw), main_window_ui(mwui) {}
    project_control(const project_control &other) = delete;
    project_control& operator=(const project_control &other) = delete;
    ~project_control() = default;

    int active();
    int add_new_project(QString name, Backend be, const QString &location);
    int add_existing_project(QString path);
    shared_ptr<project_object> operator[](int id);
    const shared_ptr<project_object> operator[](int id) const;
    shared_ptr<project_object> get_active_project();
    void save_project(int id);
    void save_active_project();
    void close_project(int id);

public slots:
    /**
    * Connected to the "New Project" button's clicked() signal
    */
    void create_new_project();
};

}


#endif // PROJECT_CONTROL_H
