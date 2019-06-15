#ifndef PARTITEM_H
#define PARTITEM_H

#include "graphmodel/graphmodel_name.h"
#include "portitem.h"
#include "modelscene.h"
#include "partinfomodel.h"


class PartItem : public QGraphicsRectItem
{
public:
    enum {Type = UserType + 1};

    ModelScene *scene() { return static_cast<ModelScene *>(QGraphicsRectItem::scene()); }
    int type() const noexcept override { return Type; }
    int id() const noexcept { return mId; }
    PortItem &inPort() noexcept { return mIn; }
    PortItem &outPort() noexcept { return mOut; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    PartItem(int id, PartType partType, const QPointF &center,
             QGraphicsItem *parent = nullptr);
private:
    PartType mPartType;

    PortItem mIn;
    PortItem mOut;

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

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // PARTITEM_H
