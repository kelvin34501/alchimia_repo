#ifndef PARTITEM_H
#define PARTITEM_H

#include <QGraphicsRectItem>

#include "graphmodel/graphmodel_name.h"


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
          mId(id)
    {
        setPos(center);
    }

private:
    PartType mPartType;

    /**
    * @var The ID Corresponding to the Part in the GraphModel
    */
    int mId;

    static const QRectF itemRect;	// all PartItems have the same rectangle

    /**
    * Distance between the left side of the name of a PartItem and the left
    * side of the rectangle, in unscaled pixels.
    */
    static const qreal textHorizontalOffset;
};

#endif // PARTITEM_H
