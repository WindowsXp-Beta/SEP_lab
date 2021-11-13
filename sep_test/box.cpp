#include "box.h"
#include "constant.h"
#include <QPainter>

Box::Box(int x, int y, Type type):x(x), y(y), type(type)
{
    value = 0;
    int xCor = -300 + x * BOX_SIZE;
    int yCor = 294 - y * BOX_SIZE;
    setPos(xCor, yCor);
}


QRectF Box::boundingRect() const
{
    return QRectF(0, 0, BOX_SIZE, BOX_SIZE);
}

void Box::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    QColor color;
    switch(type){
    case Enemy:
        color = ENEMY_COLOR;
        break;
    case Safe:
        color = SAFE_COLOR;
        break;
    case Path:
        color = PATH_COLOR;
        break;
    }
    painter->setBrush(color);
    painter->drawRect(0, 0, BOX_SIZE, BOX_SIZE);
    painter->restore();
}
