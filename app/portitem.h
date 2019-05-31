#ifndef PORTITEM_H
#define PORTITEM_H

#include <QGraphicsEllipseItem>


class PartItem;

class PortItem : public QGraphicsEllipseItem
{
public:
    PortItem(bool isOutput, PartItem *parent);

    int type() const noexcept override { return Type; }

private:
    const PartItem &mParent;
    const bool mIsOutput;

    static const QRectF itemRect;
    enum {Type = UserType + 3};
};

#endif // PORTITEM_H
