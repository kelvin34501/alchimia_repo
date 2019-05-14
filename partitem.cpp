#include <QPainter>

#include "partitem.h"


const QRectF PartItem::itemRect(-60, -30, 120, 60);
const qreal PartItem::textHorizontalOffset = 5;

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
