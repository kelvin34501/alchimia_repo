#include <QAbstractButton>

#include "modelscene.h"
#include "partitem.h"


// recieve the begin event of add part
void EditorControl::selectTemplate(int partType) const noexcept
{
    // update model scene status
    mModelScene.setClickMode(ModelScene::TemplateSelcted);
    mModelScene.selecteTemplate(static_cast<PartType>(partType));
}

// recieve the confirmation of adding part and other relative data for the part
void EditorControl::add(PartType partType, const QPointF &pos) const
{
    // add part in the graph model storage
    int id = mProject.graph_mdl->addPart(partType, static_cast<float>(pos.x()),
                                         static_cast<float>(pos.y()));

    // update model scene and related UIs
    mModelScene.addItem(new PartItem(id, partType, pos));
    mToolboxButtonGroup.checkedButton()->setChecked(false);    // uncheck the button
    mModelScene.setClickMode(ModelScene::Idle);
}
