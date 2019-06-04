#include "partitem.h"

#include <QPainter>


/*!
\class PartItem
\brief The UI for the Part class
*/

const QRectF PartItem::itemRect(-60, -30, 120, 60);
const qreal PartItem::textHorizontalOffset = 5;

/*!
\fn  PartItem::PartItem(int id, PartType partType, const QPointF &center,
                        QGraphicsItem *parent)

Assume that the point center is chosen so that the constructed PartItem won't
overlap with the boundary of the ModelScene
*/
PartItem::PartItem(int id, PartType partType, const QPointF &center,
                   QGraphicsItem *parent)
    : QGraphicsRectItem(itemRect, parent), mPartType(partType),
      mIn(false, this), mOut(true, this), mId(id)
{
    setPos(center);
    mIn.setPos(QPointF(0, -30));
    mOut.setPos(QPointF(0, 30));
    setFlags({ItemIsSelectable});
}

void PartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);

    // draw the name of the layer
    QPointF textPos = rect().topLeft();
    textPos.setX(textPos.x() + textHorizontalOffset);
    textPos.setY(textPos.y() + rect().height() / 3);
    painter->drawText(textPos, PartTypeString[static_cast<int>(mPartType)]);
}
