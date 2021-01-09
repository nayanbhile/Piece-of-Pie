#include "pointcomponent.h"

PointComponent::PointComponent()
{

}

QPointF PointComponent::getPoint() const
{
    return point;
}

void PointComponent::setPoint(const QPointF &value)
{
    point = value;
}

QPen PointComponent::getPen() const
{
    return this->pen;
}

void PointComponent::setPen(const QPen &value)
{
    this->pen = value;
}

QString PointComponent::getComponentName()
{
    return componentName;
}

void PointComponent::setComponentName(QString componentName)
{
    this->componentName=componentName;
}

QString PointComponent::getComponentType()
{
    return componentType;
}

bool PointComponent::isPointOnComponent(QPointF point)
{
    return this->point==point;
}

bool PointComponent::select(QPainter *painter, QPointF point)
{
    QPen pen("black");
    pen.setWidth(2);
    painter->setPen(pen);
    int x,y;
    x=this->point.x();
    y=this->point.y();
    if(isPointOnComponent(point))
    {
        this->draw(painter);
        painter->drawRect(x-6,y-6,12,12);
        pen.setColor("white");
        painter->setPen(pen);
        painter->drawRect(x-4,y-4,8,8);

        return true;
    }
    return false;
}

void PointComponent::select(QPainter *painter)
{
    QPen pen("black");
    pen.setWidth(2);
    painter->setPen(pen);
    int x,y;
    x=this->point.x();
    y=this->point.y();
        this->draw(painter);
        painter->drawRect(x-6,y-6,12,12);
        pen.setColor("white");
        painter->setPen(pen);
        painter->drawRect(x-4,y-4,8,8);

}

void PointComponent::draw(QPainter *painter)
{
    this->pen.setWidth(8);
    painter->setPen(this->pen);
    painter->drawPoint(this->point);
}

void PointComponent::drawOpaque(QPainter *painter)
{
    painter->save();

    painter->setPen(this->pen);
    painter->drawPoint(this->point);

    painter->restore();
}
