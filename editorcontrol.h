#ifndef EDITORCONTROL_H
#define EDITORCONTROL_H

#include <QButtonGroup>
#include <QPointF>

#include "graphmodel/graphmodel.h"


class ModelScene;

class EditorControl : public QObject
{
    Q_OBJECT
public:
    void setToolboxButtonGroup(QButtonGroup *toolboxButtonGroup) noexcept
    {
        mToolboxButtonGroup = toolboxButtonGroup;
    }

    void add(PartType partType, QPointF pos) const;

    EditorControl(ModelScene *modelScene, QObject *parent = nullptr)
        : QObject(parent), mModelScene(modelScene) {}

signals:

public slots:
    void selectTemplate(int partType) const noexcept;

private:
    ModelScene *mModelScene;
    /**
     * Must be set immediately after construction.
    */
    QButtonGroup *mToolboxButtonGroup;
};

#endif // EDITORCONTROL_H
