#ifndef PORTITEM_H
#define PORTITEM_H

#include <QGraphicsEllipseItem>


class PartItem;

class PortItem : public QGraphicsEllipseItem
{
public:
    PortItem(bool isOutput, PartItem *parent);

private:
    const PartItem &mParent;
    const bool mIsOutput;

    static const QRectF itemRect;
};

#endif // PORTITEM_H
