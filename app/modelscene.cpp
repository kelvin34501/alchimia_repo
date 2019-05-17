#include "modelscene.h"
#include "partitem.h"
#include "connectionitem.h"


const QRectF ModelScene::sceneRect(0, 0, 5000, 5000);

void ModelScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        switch (mClickMode) {
        case Idle:
            break;
        case TemplateSelcted:
            mEditorControl.add(mSelectedTemplateType, event->scenePos());
            break;
        case ConnectingParts:
            incompleteConnection = addLine(QLineF(event->scenePos(), event->scenePos()));
        }
}

void ModelScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mClickMode == ConnectingParts) {
        // update the line in incompleteConnection
        QLineF newLine = incompleteConnection->line();
        newLine.setP2(event->scenePos());
        incompleteConnection->setLine(newLine);
    }
}

void ModelScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (mClickMode == ConnectingParts && event->button() == Qt::LeftButton) {
        // PartItems at the start and end of incompleteConnection
        // The topmost item is incompleteConnection
        QList<QGraphicsItem *> startItems = items(incompleteConnection->line().p1());
        // TODO: Check empty lists
        startItems.pop_front();
        PartItem *start = static_cast<PartItem *>(startItems.front());
        QList<QGraphicsItem *> endItems = items(incompleteConnection->line().p2());
        endItems.pop_front();
        PartItem *end = static_cast<PartItem *>(endItems.front());

        removeItem(incompleteConnection);
        delete incompleteConnection;

        int id = mGraphModel.addConnection(start->id(), end->id(), true, false);
        addItem(new ConnectionItem(*start, *end, id));
        setClickMode(Idle);
        mConnectButton.setChecked(false);
    }
}
