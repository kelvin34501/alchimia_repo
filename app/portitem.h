#ifndef PORTITEM_H
#define PORTITEM_H

#include <QGraphicsEllipseItem>


class PartItem;
class ConnectionItem;

class PortItem : public QGraphicsEllipseItem
{
public:
    enum {Type = UserType + 3};

    int type() const noexcept override { return Type; }
    bool isOutput() const noexcept { return mIsOutput; }
    void setConnection(ConnectionItem *ci) noexcept { connection = ci; }

    PortItem(bool isOutput, PartItem *parent);
    ~PortItem() override;

private:
    /*!
    \variable PortItem::connection
    \brief the ConnectionItem that this PortItem is connected to
    */
    ConnectionItem *connection = nullptr;

    const bool mIsOutput;

    static const QRectF itemRect;
};

#endif // PORTITEM_H
