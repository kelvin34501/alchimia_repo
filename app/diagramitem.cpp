#include "diagramitem.h"

DiagramItem::DiagramItem(QGraphicsItem *parent) : QGraphicsPolygonItem(parent)
{
    myPolygon << QPointF(-120, -80) << QPointF(-70, 80) << QPointF(120, 80)
              << QPointF(70, -80) << QPointF(-120, -80);
    setPolygon(myPolygon);

    setFlags({
        GraphicsItemFlag::ItemIsMovable,
        GraphicsItemFlag::ItemIsSelectable,
        GraphicsItemFlag::ItemSendsGeometryChanges
    });
}
