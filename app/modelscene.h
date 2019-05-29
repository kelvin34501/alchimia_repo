#ifndef MODELSCENE_H
#define MODELSCENE_H

#include "editorcontrol.h"
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
    void selectTemplate(PartType partType) noexcept
    {
        mSelectedTemplateType = partType;
    }

    explicit ModelScene(QButtonGroup &toolboxButtonGroup,
                        project_object &project, QToolButton &connectButton,
                        QObject *parent = nullptr);

public slots:
    /**
    * Called by connectButton's clicked() to enter or exit the ConnectingParts
    * state
    *
    * @param checked: corresponds to the parameter of connectButton->checked()
    */
    void startConnection(bool checked) noexcept
    {
        checked ? setClickMode(ConnectingParts) : setClickMode(Idle);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ClickMode mClickMode;
    PartType mSelectedTemplateType;
    EditorControl mEditorControl;
    project_object &mProject;
    QGraphicsLineItem *incompleteConnection;
    QToolButton &mConnectButton;

    static const QRectF sceneRect;  // fixed-size graphics scene
};

#endif // MODELSCENE_H
