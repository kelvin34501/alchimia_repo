#ifndef MODELSCENE_H
#define MODELSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "graphmodel/graphmodel_name.h"


class EditorControl;

class ModelScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum ClickMode {Idle, TemplateSelcted};

    void setClickMode(ClickMode clickMode) noexcept { mClickMode = clickMode; }
    void selecteTemplate(PartType partType) noexcept
    {
        mSelectedTemplateType = partType;
    }
    void setEditorControl(EditorControl *editorControl) noexcept
    {
        mEditorControl = editorControl;
    }

    explicit ModelScene(EditorControl *editorControl = nullptr, QObject *parent = nullptr)
        : QGraphicsScene(sceneRect, parent), mClickMode(Idle),
          mEditorControl(editorControl) {}

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ClickMode mClickMode;
    PartType mSelectedTemplateType;
    EditorControl *mEditorControl;

    static const QRectF sceneRect;  // fixed-size graphics scene
};

#endif // MODELSCENE_H
