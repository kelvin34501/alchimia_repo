#ifndef PARTITEM_H
#define PARTITEM_H

#include "graphmodel/graphmodel_name.h"
#include "portitem.h"


class PartItem : public QGraphicsRectItem
{
public:
    int id() const noexcept { return mId; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    /**
     * Assume that the point center is chosen so that the constructed
     * PartItem won't overlap with the boundary of the ModelScene
    */
    PartItem(int id, PartType partType, const QPointF &center,
             QGraphicsItem *parent = nullptr)
        : QGraphicsRectItem(itemRect, parent), mPartType(partType),
          mIn(false, this), mOut(true, this), mId(id)
    {
        setPos(center);
        mIn.setPos(QPointF(0, -30));
        mOut.setPos(QPointF(0, 30));
    }

private:
    PartType mPartType;

    PortItem mIn;
    PortItem mOut;

    /**
    * @var The ID Corresponding to the Part in the GraphModel
    */
    int mId;

    enum {Type = UserType + 1};
    static const QRectF itemRect;	// all PartItems have the same rectangle

    /**
    * Distance between the left side of the name of a PartItem and the left
    * side of the rectangle, in unscaled pixels.
    */
    static const qreal textHorizontalOffset;

    int type() const noexcept override { return Type; }
};

#endif // PARTITEM_H
