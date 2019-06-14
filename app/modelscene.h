#ifndef MODELSCENE_H
#define MODELSCENE_H

#include "project/project_object.h"
#include "partinfomodel.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QToolButton>
#include <QTreeView>


using namespace project;

class PartItem;

class ModelScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum ClickMode {Idle, TemplateSelected, ConnectingParts};

    void setClickMode(ClickMode clickMode) noexcept { mClickMode = clickMode; }
    void displayPartInfo(int partId);
    void clearPartInfo() { partInfoModel.clear(); }

    ModelScene(QButtonGroup &toolboxButtonGroup, QTreeView &tv,
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
    void updateInfoDisplay();

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

    /*!
    \variable ModelScene::partInfoModel
    \brief The PartInfoModel associated with QTreeView
    */
    PartInfoModel partInfoModel;

    static const QRectF sceneRect;  // fixed-size graphics scene
};

#endif // MODELSCENE_H
