#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include <QGraphicsLineItem>

#include "partitem.h"


class ConnectionItem : public QGraphicsLineItem
{
public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
               QWidget *) override;

    ConnectionItem(PartItem &start, PartItem &end) : mStart(start), mEnd(end)
    {
        setPos(mStart.pos());
        setZValue(-100);	// place connections below parts
    }

private:
    PartItem &mStart, &mEnd;
    QPolygonF mArrowHead;

    /**
    * @var The size of the arrow head
    */
    static const qreal arrowSize;
};

#endif // CONNECTIONITEM_H
