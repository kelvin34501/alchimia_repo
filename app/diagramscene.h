#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H
#include <QGraphicsScene>


class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {InsertItem, InsertLine, InsertText, MoveItem};

    explicit DiagramScene(QObject *parent = nullptr);

private:
    Mode myMode;
};

#endif // DIAGRAMSCENE_H
