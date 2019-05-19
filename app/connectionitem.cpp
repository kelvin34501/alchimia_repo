#include "connectionitem.h"

#include <QPainter>
#include <cmath>

#ifdef M_PI
#undef M_PI
#endif
const double M_PI = 4 * std::atan(1);


const qreal ConnectionItem::arrowSize = 10;

QRectF ConnectionItem::boundingRect() const
{
    qreal extra = 10;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath ConnectionItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(mArrowHead);
    return path;
}

void ConnectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                           QWidget *)
{
    if (mStart.collidesWithItem(&mEnd))
        return;

    using std::sin;
    using std::cos;
    painter->setBrush(Qt::black);

    // use the scene coordinate throughout computation
    QLineF centerLine(mStart.pos(), mEnd.pos());
    // find the intersection between the connection and the edges of the
    // PartItem at the end of the connection
    // v1 is the top left vertex in the scene coordinate
    QPointF v1 = mEnd.rect().topLeft() + mEnd.pos();
    QVector<QPointF> vertices = {
        mEnd.rect().topRight(), mEnd.rect().bottomRight(),
        mEnd.rect().bottomLeft(), mEnd.rect().topLeft()
    };
    QPointF intersection;
    for (QVector<QPointF>::size_type i = 0; i < vertices.size(); ++i) {
        QPointF v2 = vertices.at(i) + mEnd.pos();
        QLineF edge = QLineF(v1, v2);	// for each edge
        QLineF::IntersectType intersectType = edge.intersect(centerLine, &intersection);
        if (intersectType == QLineF::BoundedIntersection)
            break;
        v1 = v2;
    }
    setLine(QLineF(mapFromScene(intersection), QPointF(0, 0)));

    // draw the arrow head
    double angle = std::atan2(-line().dy(), line().dx());
    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                    cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                    cos(angle + M_PI - M_PI / 3) * arrowSize);

    mArrowHead.clear();
    mArrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawPolygon(mArrowHead);
    if (isSelected()) {
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}
