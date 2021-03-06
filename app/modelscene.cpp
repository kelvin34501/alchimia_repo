#include "modelscene.h"
#include "partitem.h"
#include "connectionitem.h"
#include "utils/exceptions.h"

#include <QButtonGroup>
#include <QMessageBox>
#include <QKeyEvent>


/*!
\class ModelScene

Assumed that batch selection is not supported. This assumption is needed
for editPart().
*/

const QRectF ModelScene::sceneRect(0, 0, 5000, 5000);

/*!
\fn void ModelScene::displayPartInfo(int partId)
\brief Display the parameters of a Part for editing when it is selected.
*/
void ModelScene::displayPartInfo(int partId)
{
    auto info = mProject.graph_mdl->getPartInfo(partId);
    partInfoModel.storePartInfo(info);
    treeView.resizeColumnToContents(0);
}

ModelScene::ModelScene(QButtonGroup &toolboxButtonGroup, QTreeView &tv,
                       project_object &project, QObject *parent)
    : QGraphicsScene(sceneRect, parent), mClickMode(Idle),
      mToolboxButtonGroup(toolboxButtonGroup), treeView(tv), mProject(project)
{
    treeView.setModel(&partInfoModel);

    connect(&toolboxButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(selectTemplate(int)));
    connect(&partInfoModel, SIGNAL(itemChanged(QStandardItem *)),
            this, SLOT(editPart(QStandardItem *)));

    // If GraphModel has parts and connections, redraw them on the ModelScene.
    // store created PartItems in a temporary vector, ordered by their IDs
    std::vector<PartItem *> v(mProject.graph_mdl->parts.size());
    for (auto i = mProject.graph_mdl->parts.begin(); i < mProject.graph_mdl->parts.end(); ++i) {
        std::shared_ptr<Part> p = *i;
        if (p) {
            PartItem *partItem = new PartItem(
                p->id,
                p->parttype,
                QPointF(static_cast<double>(p->position_x), static_cast<double>(p->position_y))
            );
            this->addItem(partItem);
            v[static_cast<std::vector<PartItem *>::size_type>(partItem->id())] = partItem;
        }
    }
    typedef std::vector<PartItem *>::size_type size_type;
    for (std::vector<std::shared_ptr<Connection>>::size_type i = 0;
         i < mProject.graph_mdl->connections.size(); ++i) {
        std::shared_ptr<Connection> c = mProject.graph_mdl->connections[i];
        if (c) {
            auto startId = static_cast<size_type>(c->ports[0].lock()->part.lock()->id);
            auto endId = static_cast<size_type>(c->ports[1].lock()->part.lock()->id);
            this->addItem(new ConnectionItem(v[startId]->outPort(), v[endId]->inPort(), c->id));
        }
    }
}

/*!
\fn void ModelScene::editPart(QStandardItem *item)
\brief Connected to PartInfoModel::itemChanged()
*/
void ModelScene::editPart(QStandardItem *item)
{
    std::string paramValue(item->data(Qt::DisplayRole).toString().toStdString());
    // Each parameter of a Part is a key-value pair
    // retrieve the key here
    QStandardItem *paramNameItem = partInfoModel.item(item->row());
    std::string paramName(paramNameItem->data(Qt::DisplayRole).toString().toStdString());
    try {
        // assumed batch selection is not supported
        auto partItem = static_cast<PartItem *>(selectedItems().front());
        mProject.graph_mdl->editPart(partItem->id(), paramName, paramValue);
        partInfoModel.clear();
        displayPartInfo(partItem->id());
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

/*!
\fn void ModelScene::updateInfoDisplay()
\brief Connected to DataConfigurationDialog::modelUpdated
*/
void ModelScene::updateInfoDisplay()
{
    if (partInfoModel.rowCount() == 0)
        return;
    // now there must be a selected PartItem
    auto partItem = static_cast<PartItem *>(selectedItems().front());
    auto info = mProject.graph_mdl->getPartInfo(partItem->id());
    partInfoModel.clear();
    partInfoModel.storePartInfo(info);
    treeView.resizeColumnToContents(0);
}

/*!
\fn ModelScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
*/
void ModelScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        switch (mClickMode) {
        case Idle: {
            // retrieve the top item at the click position and see whether it
            // is a PortItem
            QList<QGraphicsItem *> l = items(event->scenePos());
            if (!l.empty() && qgraphicsitem_cast<PortItem *>(l.front())) {
                setClickMode(ConnectingParts);
                incompleteConnection = addLine(QLineF(event->scenePos(), event->scenePos()));
            }
            else	// handle item selection and movement
                QGraphicsScene::mousePressEvent(event);
            break;
        }
        case TemplateSelected: {
            QPointF scenePos = event->scenePos();
            // add part in the graph model storage
            int id = mProject.graph_mdl->addPart(
                        mSelectedTemplateType,
                        static_cast<float>(scenePos.x()),
                        static_cast<float>(scenePos.y())
            );

            // update model scene and related UIs
            addItem(new PartItem(id, mSelectedTemplateType, scenePos));
            // uncheck the button
            mToolboxButtonGroup.checkedButton()->setChecked(false);
            setClickMode(Idle);
            break;
        }
        case ConnectingParts:
            break;
        }
}

void ModelScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mClickMode == ConnectingParts) {
        // update the line in incompleteConnection
        QLineF newLine = incompleteConnection->line();
        newLine.setP2(event->scenePos());
        incompleteConnection->setLine(newLine);
    } else	// handle item movement
        QGraphicsScene::mouseMoveEvent(event);
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
        setClickMode(Idle);

        // if there is no part under the cursor.
        if (startItems.empty() || endItems.empty())
            return;

        auto endPort = qgraphicsitem_cast<PortItem *>(endItems.front());
        if (!endPort)   // there is no port under incompleteConnection->line().p1()
            return;
        // assume that the start position is valid i.e. there is a port under
        // incompleteConnection->line().p1()
        auto startPort = static_cast<PortItem *>(startItems.front());
        // startPort must be an output port and endPort must be an input port.
        if (startPort->isOutput() && !endPort->isOutput()) {
            auto start = static_cast<PartItem *>(startPort->parentItem());
            auto end = static_cast<PartItem *>(endPort->parentItem());

            int id = mProject.graph_mdl->addConnection(start->id(), end->id(), true, false);
            addItem(new ConnectionItem(*startPort, *endPort, id));
        } else { // inform the user of I/O mismatch
            QMessageBox msg;
            msg.setText("Ports can only be connected in the direction from an "
                        "output port to an input port.");
            msg.exec();
        }
    } else {
        auto item = qgraphicsitem_cast<PartItem *>(mouseGrabberItem());
        // update the position of Part in GraphModel
        if (item) {
            using namespace std;
            auto part = mProject.graph_mdl->parts[static_cast<vector<shared_ptr<Part>>::size_type>(item->id())];
            part->position_x = static_cast<float>(item->pos().x());
            part->position_y = static_cast<float>(item->pos().y());
        }
        // handle item selection and movement
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

/*!
\fn void ModelScene::keyPressEvent(QKeyEvent *event)
\brief Reimplemented to support deleting ConnectionItem and PartItem with the
"Del" key.
*/
void ModelScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        QList<QGraphicsItem *> l = selectedItems();
        if (!l.empty()) {
            switch (l.front()->type()) {
            case ConnectionItem::Type: {
                auto item = static_cast<ConnectionItem *>(l.front());
                mProject.graph_mdl->deleteConnection(item->id());
                removeItem(item);
                delete item;
                break;
            }
            case PartItem::Type: {
                auto item = static_cast<PartItem *>(l.front());
                mProject.graph_mdl->deletePart(item->id());
                partInfoModel.clear();
                removeItem(item);
                delete item;
                break;
            }
            }
        }
    }
}
