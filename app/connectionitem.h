#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include "partitem.h"


/**
* @class Representation of a Connection in the UI
*
* The origin of the item coordinate is mStart.pos().
*/
class ConnectionItem : public QGraphicsLineItem
{
public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
               QWidget *) override;

    ConnectionItem(PartItem &start, PartItem &end, int id)
        : mStart(start), mEnd(end), mId(id)
    {
        setZValue(-100);	// place connections below parts
        setPos(mStart.pos());
    }

private:
    PartItem &mStart, &mEnd;
    QPolygonF mArrowHead;

    /**
    * @var ID of the corresponding connection in GraphModel
    */
    int mId;

    /**
    * @var The size of the arrow head
    */
    static const qreal arrowSize;
};

#endif // CONNECTIONITEM_H
