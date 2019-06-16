#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include "portitem.h"


class ConnectionItem : public QGraphicsLineItem
{
public:
    enum {Type = UserType + 2};

    int id() const noexcept { return mId; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
               QWidget *) override;

    ConnectionItem(PortItem &start, PortItem &end, int id);
    ~ConnectionItem() noexcept override
    {
        mStart.setConnection(nullptr);
        mEnd.setConnection(nullptr);
    }

    int type() const noexcept override { return Type; }

private:
    PortItem &mStart, &mEnd;
    QPolygonF mArrowHead;

    /*!
    \variable ConnectionItem::mId
    \brief ID of the corresponding connection in GraphModel
    */
    const int mId;

    /**
    * @var The size of the arrow head
    */
    static const qreal arrowSize;
};

#endif // CONNECTIONITEM_H
