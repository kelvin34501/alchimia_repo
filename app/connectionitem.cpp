#include "connectionitem.h"

#include <QPainter>
#include <cmath>
#include <QDebug>

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

    QLineF centerLine(QPointF(0, 0), mapFromScene(mEnd.scenePos()));
    qreal radius = mEnd.rect().width() / 2;
    qreal ratio = 1 - radius / centerLine.length();
    // the intersection between the line connecting two centers of PortItems
    // and mEnd's circle
    QPointF intersection = QPointF(centerLine.dx(), centerLine.dy()) * ratio;
    centerLine.setP2(intersection);
    setLine(centerLine);
    painter->drawLine(line());

    // draw the arrow head
    double angle = std::atan2(line().dy(), line().dx());
    QPointF arrowP1 = line().p2()
            + QPointF(cos(5 * M_PI / 6 + angle), sin(5 * M_PI / 6 + angle)) * arrowSize;
    QPointF arrowP2 = line().p2()
            + QPointF(cos(7 * M_PI / 6 + angle), sin(7 * M_PI / 6 + angle)) * arrowSize;
    mArrowHead.clear();
    mArrowHead << line().p2() << arrowP1 << arrowP2;
    painter->drawPolygon(mArrowHead);

    if (isSelected()) {
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}
