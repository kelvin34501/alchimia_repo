#ifndef ARROW_H
#define ARROW_H

#include <cmath>
#include <QGraphicsLineItem>
#include <QPainter>

#include "diagramitem.h"


class Arrow : public QGraphicsLineItem
{
public:
    Arrow(DiagramItem *startItem, DiagramItem *endItem, QGraphicsItem *parent = nullptr);
    ~Arrow() {}

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
private:
    DiagramItem *myStartItem;
    DiagramItem *myEndItem;
    QColor myColor = Qt::black;
    QPolygonF arrowHead;
};

#endif // ARROW_H
