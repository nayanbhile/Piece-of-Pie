#include "freehandcomponent.h"

FreeHandComponent::FreeHandComponent()
{
    componentName=componentType;
}

QString FreeHandComponent::getComponentName()
{
    return componentName;
}

void FreeHandComponent::draw(QPainter *painter)
{
    painter->save();

    painter->setPen(this->pen);
    for(int i=1;i<xList.size();i++)
    {
        painter->drawLine(QPointF(xList.at(i-1),yList.at(i-1)),QPointF(xList.at(i),yList.at(i)));
    }
    painter->restore();
}

void FreeHandComponent::drawOpaque(QPainter *painter)
{
    painter->save();
    painter->setOpacity(0.5);
    painter->setPen(this->pen);
    for(int i=1;i<xList.size();i++)
    {
        painter->drawLine(QPointF(xList.at(i-1),yList.at(i-1)),QPointF(xList.at(i),yList.at(i)));
    }
    painter->restore();
}

QString FreeHandComponent::getComponentType()
{
    return componentType;
}

void FreeHandComponent::select(QPainter *painter)
{
    int x1,y1;
    painter->save();
    QPen pen("black");
    pen.setWidth(2);
    painter->setPen(pen);
    for(int i=0;i<xList.size();i++)
    {
        if(i%25==0)
        {
            x1=xList.at(i);
            y1=yList.at(i);
            painter->drawRect(x1-6,y1-6,12,12);
            pen.setColor("white");
            painter->drawRect(x1-4,y1-4,8,8);
            pen.setColor("black");
        }
    }
    x1=xList.back();
    y1=yList.back();
    painter->drawRect(x1-6,y1-6,12,12);
    pen.setColor("white");
    painter->drawRect(x1-4,y1-4,8,8);
    pen.setColor("black");
    painter->restore();
}

void FreeHandComponent::setComponentName(QString name)
{
    componentName=name;
}

bool FreeHandComponent::select(QPainter *painter, QPointF point)
{
    if(isPointOnComponent(point))
    {
        int x1,y1;
        painter->save();
        QPen pen("black");
        pen.setWidth(2);
        painter->setPen(pen);
        for(int i=0;i<xList.size();i++)
        {
            if(i%25==0)
            {
                x1=xList.at(i);
                y1=yList.at(i);
                painter->drawRect(x1-6,y1-6,12,12);
                pen.setColor("white");
                pen.setWidth(3);
                painter->setPen(pen);
                painter->drawRect(x1-4,y1-4,8,8);
                pen.setColor("black");
            }
        }
        pen.setColor("black");
        x1=xList.back();
        y1=yList.back();
        painter->drawRect(x1-6,y1-6,12,12);
        pen.setColor("white");
        pen.setWidth(3);
        painter->setPen(pen);
        painter->drawRect(x1-4,y1-4,8,8);
        painter->restore();
        return true;
    }
    else return false;

}

bool FreeHandComponent::isPointOnComponent(QPointF point)
{
    int x,y;
    QPointF tmpPoint;
    for(int i=0;i<xList.size();i++)
    {
        for(int j=-2;j<3;j++)
        {
            for(int k=-4;k<=4;k++)
            {
            x=xList.at(i)+j;
            y=yList.at(i)+k;
            tmpPoint=QPointF(x,y);
        if(point==tmpPoint) return true;
            }
        }
    }
    return false;
}

QPen FreeHandComponent::getPen() const
{
    return pen;
}

void FreeHandComponent::setPen(const QPen &value)
{
    pen = value;
}

QList<int> FreeHandComponent::getXList() const
{
    return xList;
}

void FreeHandComponent::setXList(const QList<int> &value)
{
    xList = value;
}

QList<int> FreeHandComponent::getYList() const
{
    return yList;
}

void FreeHandComponent::setYList(const QList<int> &value)
{
    yList = value;
}
