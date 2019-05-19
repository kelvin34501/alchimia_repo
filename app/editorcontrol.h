#ifndef EDITORCONTROL_H
#define EDITORCONTROL_H

#include <QButtonGroup>
#include <QPointF>

#include "project/project_object.h"


using namespace project;

class ModelScene;

class EditorControl : public QObject
{
    Q_OBJECT
public:
    /**
    * @param pos: the scene coordinate of the PartItem to add
    */
    void add(PartType partType, const QPointF &pos) const;

    EditorControl(ModelScene &modelScene, QButtonGroup &toolboxButtonGroup,
                  project_object &project, QObject *parent = nullptr)
        : QObject(parent), mModelScene(modelScene),
          mToolboxButtonGroup(toolboxButtonGroup), mProject(project)
    {
        connect(&toolboxButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(selectTemplate(int)));
    }

signals:

public slots:
    void selectTemplate(int partType) const noexcept;

private:
    ModelScene &mModelScene;
    /**
    * @var The QButtonGroup that is associated with the EditorControl
    */
    QButtonGroup &mToolboxButtonGroup;

    project_object &mProject;
};

#endif // EDITORCONTROL_H
