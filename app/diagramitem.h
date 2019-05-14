#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H
#include <QGraphicsPolygonItem>


class DiagramItem : public QGraphicsPolygonItem
{
private:
    QPolygonF myPolygon;
public:
    DiagramItem(QGraphicsItem *parent = nullptr);
};

#endif // DIAGRAMITEM_H
