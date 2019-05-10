#include "arrow.h"

Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), myStartItem(startItem), myEndItem(endItem)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    if (myStartItem->collidesWithItem(myEndItem))
        return;

    // QPen myPen = pen();
    qreal arrowSize = 20;
    painter->setPen(pen());
    painter->setBrush(myColor);
    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
    QPolygonF endPolygon = myEndItem->polygon();
    // first vertex of myEndItem
    QPointF p1 = endPolygon.first() + myEndItem->pos();
    QPointF p2, intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i) {
        // p1 and p2 forms an edge of endPolygon
        p2 = endPolygon.at(i) + myEndItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    // adjust the length of the arrow
    setLine(QLineF(intersectPoint, myStartItem->pos()));
    double angle = std::atan2(-line().dy(), line().dx());

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                    cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                    cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4);
        painter->drawLine(myLine);
        myLine.translate(0, -8);
        painter->drawLine(myLine);
    }
}
