#include <QAbstractButton>

#include "editorcontrol.h"
#include "modelscene.h"
#include "partitem.h"


void EditorControl::add(PartType partType, const QPointF &pos) const
{
    // TODO: Add the part to the GraphModel
    mModelScene->addItem(new PartItem(pos));
    mToolboxButtonGroup->checkedButton()->setChecked(false);    // uncheck the button
    mModelScene->setClickMode(ModelScene::Idle);
}

void EditorControl::selectTemplate(int partType) const noexcept
{
    mModelScene->setClickMode(ModelScene::TemplateSelcted);
    mModelScene->selecteTemplate(static_cast<PartType>(partType));
}
