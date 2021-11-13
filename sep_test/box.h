#ifndef BOX_H
#define BOX_H

#include <QGraphicsItem>

class Box : public QGraphicsItem
{
public:
    enum Type{
        Enemy, Safe, Path
    };
    int x;
    int y;
    Type type;
    int value;//for bfs

    Box();
    void draw();

    Box(int x, int y, Type type = Safe);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BOX_H
