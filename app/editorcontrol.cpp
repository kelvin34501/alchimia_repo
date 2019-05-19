#include <QAbstractButton>

#include "modelscene.h"
#include "partitem.h"


void EditorControl::add(PartType partType, const QPointF &pos) const
{
    int id = mProject.graph_mdl->addPart(partType, static_cast<float>(pos.x()),
                                         static_cast<float>(pos.y()));
    mModelScene.addItem(new PartItem(id, partType, pos));
    mToolboxButtonGroup.checkedButton()->setChecked(false);    // uncheck the button
    mModelScene.setClickMode(ModelScene::Idle);
}

void EditorControl::selectTemplate(int partType) const noexcept
{
    mModelScene.setClickMode(ModelScene::TemplateSelcted);
    mModelScene.selecteTemplate(static_cast<PartType>(partType));
}
