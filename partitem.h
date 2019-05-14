#ifndef PARTITEM_H
#define PARTITEM_H

#include <QGraphicsRectItem>

#include "graphmodel/graphmodel_name.h"


class PartItem : public QGraphicsRectItem
{
public:
    /**
     * Assume that the point center is chosen so that the constructed
     * PartItem won't overlap with the boundary of the ModelScene
    */
    PartItem(const QPointF &center, QGraphicsItem *parent = nullptr)
        : QGraphicsRectItem(itemRect, parent), mPartType(PartType::InputLayer)
    {
        setPos(center);
    }

private:
    PartType mPartType;

    static const QRectF itemRect;	// all PartItems have the same rectangle
};

#endif // PARTITEM_H
