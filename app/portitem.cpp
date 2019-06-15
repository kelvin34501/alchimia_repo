#include "portitem.h"
#include "partitem.h"

#include <QBrush>


/*!
\class PortItem
\brief The UI element of a port, represented by a circle.
*/

/*!
\variable PortItem::itemRect
\brief All PortItems have the same size, as dictated by itemRect.
*/
const QRectF PortItem::itemRect(-5, -5, 10, 10);

PortItem::PortItem(bool isOutput, PartItem *parent)
    : QGraphicsEllipseItem(itemRect, parent), mIsOutput(isOutput)
{
    setBrush(QBrush(Qt::SolidPattern));
}
