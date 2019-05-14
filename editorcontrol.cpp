#include <QAbstractButton>

#include "modelscene.h"
#include "partitem.h"


void EditorControl::add(PartType partType, const QPointF &pos) const
{
    /* int id = */mGraphModel.addPart(partType, static_cast<float>(pos.x()), static_cast<float>(pos.y()));
    mModelScene.addItem(new PartItem(0, pos));
    mToolboxButtonGroup.checkedButton()->setChecked(false);    // uncheck the button
    mModelScene.setClickMode(ModelScene::Idle);
}

void EditorControl::selectTemplate(int partType) const noexcept
{
    mModelScene.setClickMode(ModelScene::TemplateSelcted);
    mModelScene.selecteTemplate(static_cast<PartType>(partType));
}
