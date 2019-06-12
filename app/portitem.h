#ifndef PORTITEM_H
#define PORTITEM_H

#include <QGraphicsEllipseItem>


class PartItem;

class PortItem : public QGraphicsEllipseItem
{
public:
    enum {Type = UserType + 3};

    int type() const noexcept override { return Type; }
    bool isOutput() const noexcept { return mIsOutput; }

    PortItem(bool isOutput, PartItem *parent);

private:
    const bool mIsOutput;

    static const QRectF itemRect;
};

#endif // PORTITEM_H
