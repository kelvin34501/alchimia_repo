#include "modelscene.h"
#include "editorcontrol.h"


const QRectF ModelScene::sceneRect(0, 0, 5000, 5000);

void ModelScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        switch (mClickMode) {
        case Idle:
            break;
        case TemplateSelcted:
            mEditorControl->add(mSelectedTemplateType, event->scenePos());
        }
}
