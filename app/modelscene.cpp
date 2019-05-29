#include "modelscene.h"
#include "partitem.h"
#include "connectionitem.h"


const QRectF ModelScene::sceneRect(0, 0, 5000, 5000);

ModelScene::ModelScene(QButtonGroup &toolboxButtonGroup, project_object &project,
                       QToolButton &connectButton, QObject *parent)
    : QGraphicsScene(sceneRect, parent), mClickMode(Idle),
      mEditorControl(*this, toolboxButtonGroup, project), mProject(project),
      mConnectButton(connectButton)
{
    connect(&connectButton, SIGNAL(clicked(bool)), this, SLOT(startConnection(bool)));

    // If GraphModel has parts and connections, redraw them on the ModelScene.
    // store created PartItems in a temporary vector, ordered by their IDs
    std::vector<PartItem *> v(mProject.graph_mdl->parts.size());
    for (std::vector<std::shared_ptr<Part>>::size_type i = 0;
         i < mProject.graph_mdl->parts.size(); ++i) {
        std::shared_ptr<Part> p = mProject.graph_mdl->parts[i];
        PartItem *partItem = new PartItem(
            p->id,
            p->parttype,
            QPointF(static_cast<double>(p->position_x), static_cast<double>(p->position_y))
        );
        this->addItem(partItem);
        v[static_cast<std::vector<PartItem *>::size_type>(partItem->id())] = partItem;
    }
    for (std::vector<std::shared_ptr<Connection>>::size_type i = 0;
         i < mProject.graph_mdl->connections.size(); ++i) {
        std::shared_ptr<Connection> c = mProject.graph_mdl->connections[i];
        auto startId = static_cast<std::vector<PartItem *>::size_type>(c->ports[0].lock()->part.lock()->id);
        auto endId = static_cast<std::vector<PartItem *>::size_type>(c->ports[1].lock()->part.lock()->id);
        this->addItem(new ConnectionItem(*v[startId], *v[endId], c->id));
    }
}

void ModelScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        switch (mClickMode) {
        case Idle:
            break;
        case TemplateSelected:
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
        startItems.pop_front();
        QList<QGraphicsItem *> endItems = items(incompleteConnection->line().p2());
        endItems.pop_front();
        removeItem(incompleteConnection);
        delete incompleteConnection;

        // Don't change the state of ModelScene if there is no part under
        // the cursor.
        if (startItems.empty() || endItems.empty())
            return;

        PartItem *start = static_cast<PartItem *>(startItems.front());
        PartItem *end = static_cast<PartItem *>(endItems.front());

        int id = mProject.graph_mdl->addConnection(start->id(), end->id(), true, false);
        addItem(new ConnectionItem(*start, *end, id));
        setClickMode(Idle);
        mConnectButton.setChecked(false);
    }
}
