#ifndef PARTITEM_H
#define PARTITEM_H

#include <QGraphicsRectItem>


class PartItem : public QGraphicsRectItem
{
private:
    static const QSizeF itemSize;  // all PartItems have the same size
public:
    /**
     * Assume that the point topleft is chosen so that the constructed
     * PartItem won't overlap with the boundary of the ModelScene
    */
    PartItem(const QPointF &topleft, QGraphicsItem *parent = nullptr)
        : QGraphicsRectItem(QRectF(topleft, itemSize), parent)
    {

    }
};

#endif // PARTITEM_H
