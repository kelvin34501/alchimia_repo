#ifndef MODELSCENE_H
#define MODELSCENE_H

#include "project/project_object.h"
#include "partinfomodel.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QToolButton>
#include <QTreeView>


using namespace project;

class ModelScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum ClickMode {Idle, TemplateSelected, ConnectingParts};

    void setClickMode(ClickMode clickMode) noexcept { mClickMode = clickMode; }
    void displayPartInfo(int partId, PartInfoModel &model) const;
    void addItem(QGraphicsItem *item) { QGraphicsScene::addItem(item); }
    void addItem(PartItem * item);

    explicit ModelScene(QButtonGroup &toolboxButtonGroup, QTreeView &tv,
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

    void editPart(QStandardItem *item) const;

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

    /*!
    \variable ModelScene::treeView
    \brief The QTreeView object associated with this ModelScene
    */
    QTreeView &treeView;

    project_object &mProject;
    QGraphicsLineItem *incompleteConnection;

    static const QRectF sceneRect;  // fixed-size graphics scene
};

#endif // MODELSCENE_H
