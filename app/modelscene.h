#ifndef MODELSCENE_H
#define MODELSCENE_H

#include "project/project_object.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QToolButton>

using std::shared_ptr;
using namespace project;

class ModelScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum ClickMode {Idle, TemplateSelected, ConnectingParts};

    void setClickMode(ClickMode clickMode) noexcept { mClickMode = clickMode; }

    explicit ModelScene(QButtonGroup &toolboxButtonGroup,
                        project_object &project, QObject *parent = nullptr);

private slots:
    /**
    * Connected to the QButtonGroup's clicked()
    *
    * @param partType: The ID of the button clicked, mapped to PartType
    */
    void selectTemplate(int partType) noexcept
    {
        setClickMode(ModelScene::TemplateSelected);
        mSelectedTemplateType = static_cast<PartType>(partType);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ClickMode mClickMode;
    PartType mSelectedTemplateType;

    /**
    * @var The QButtonGroup that is associated with the EditorControl
    */
    QButtonGroup &mToolboxButtonGroup;

    project_object &mProject;
    QGraphicsLineItem *incompleteConnection;

    static const QRectF sceneRect;  // fixed-size graphics scene
};

#endif // MODELSCENE_H
