#include "rectanglecomponent.h"

RectangleComponent::RectangleComponent()
{
    componentName=componentType;
}

QRect RectangleComponent::getRectangle() const
{
    return rectangle;
}

void RectangleComponent::setRectangle(const QRect &value)
{
    rectangle = value;
}

QPen RectangleComponent::getPen() const
{
    return pen;
}

void RectangleComponent::setPen(const QPen &value)
{
    pen = value;
}

/*
QJsonObject RectangleComponent::createJsonObject()
{
    RectangleComponent *rectangleComponent=(RectangleComponent *)this;
    QPen pen=rectangleComponent->getPen();
    int r,g,b,penWidth,x1,x2,y1,y2;
    pen.color().getRgb(&r,&g,&b);
    penWidth=pen.width();
    QRect rectangle=rectangleComponent->getRectangle();
    rectangle.getCoords(&x1,&y1,&x2,&y2);


    QJsonObject jsonLine;
    jsonLine.insert("name","Rectangle");
    jsonLine.insert("penColorR",r);
    jsonLine.insert("penColorG",g);
    jsonLine.insert("penColorB",b);
    jsonLine.insert("penWidth",penWidth);
    jsonLine.insert("filledColor",rectangleComponent->getFilledColor());
    jsonLine.insert("x1",x1);
    jsonLine.insert("x2",x2);
    jsonLine.insert("y1",y1);
    jsonLine.insert("y2",y2);
    return jsonLine;
}

DrawableComponents *RectangleComponent::readJsonObject(QJsonObject object)
{
    int r,g,b,penWidth,x1,x2,y1,y2;
    r=object.take("penColorR").toInt();
    g=object.take("penColorG").toInt();
    b=object.take("penColorB").toInt();
    penWidth=object.take("penWidth").toInt();
    QString filledColor=object.take("filledColor").toString();
    x1=object.take("x1").toInt();
    x2=object.take("x2").toInt();
    y1=object.take("y1").toInt();
    y2=object.take("y2").toInt();

    RectangleComponent *component=new RectangleComponent;
    component->setRectangle(QRect(x1,y1,x2-x1,y2-y1));
    QPen pen;
    pen.setColor(QColor(r,g,b));
    pen.setWidth(penWidth);
    component->setPen(pen);
    component->setFilledColor(filledColor);
    return component;
}

*/


void RectangleComponent::draw(QPainter *painter)
{
    painter->save();
    QBrush brush;
    QPainterPath path;
    QRect rectangle(this->getRectangle());
    QColor filledColor=this->getFilledColor();
    painter->setPen(this->getPen());
    if(filledColor=="None")
    {
        painter->drawRect(rectangle);
    }
    else
    {
        brush.setColor(filledColor);
        brush.setStyle(Qt::SolidPattern);
        path.addRect(rectangle);
        painter->fillPath(path,brush);
        painter->drawRect(rectangle);
    }
    painter->restore();
}

bool RectangleComponent::select(QPainter *painter, QPointF point)
{
    int selectedX=point.x();
    int selectedY=point.y();
    QRect rectangle=this->getRectangle();
    QPen pen("black");
    pen.setWidth(2);
    painter->setPen(pen);
    int x1,x2,y1,y2;
    rectangle.getCoords(&x1,&y1,&x2,&y2);
    if(selectedX>=x1 && selectedX<=x2 && selectedY>=y1 && selectedY<=y2)
    {
        this->draw(painter);
        painter->drawRect(x1-6,y1-6,12,12);
        painter->drawRect(x2-6,y2-6,12,12);
        painter->drawRect(x2-6,y2-6-rectangle.height(),12,12);
        painter->drawRect(x2-6-rectangle.width(),y2-6,12,12);
        pen.setColor("white");
        painter->setPen(pen);
        painter->drawRect(x1-4,y1-4,8,8);
        painter->drawRect(x2-4,y2-4,8,8);
        painter->drawRect(x2-4,y2-4-rectangle.height(),8,8);
        painter->drawRect(x2-4-rectangle.width(),y2-4,8,8);

        pen.setColor("black");
        pen.setWidth(5);
        pen.setStyle(Qt::DashDotLine);
        painter->setPen(pen);
        painter->drawRect(rectangle);
        return true;
    }
    return false;
}

void RectangleComponent::select(QPainter *painter)
{
    QRect rectangle=this->getRectangle();
    QPen pen("black");
    pen.setWidth(2);
    painter->setPen(pen);
    int x1,x2,y1,y2;
    rectangle.getCoords(&x1,&y1,&x2,&y2);
    this->draw(painter);
    painter->drawRect(x1-6,y1-6,12,12);
    painter->drawRect(x2-6,y2-6,12,12);
    painter->drawRect(x2-6,y2-6-rectangle.height(),12,12);
    painter->drawRect(x2-6-rectangle.width(),y2-6,12,12);
    pen.setColor("white");
    painter->setPen(pen);
    painter->drawRect(x1-4,y1-4,8,8);
    painter->drawRect(x2-4,y2-4,8,8);
    painter->drawRect(x2-4,y2-4-rectangle.height(),8,8);
    painter->drawRect(x2-4-rectangle.width(),y2-4,8,8);

    pen.setColor("black");
    pen.setWidth(5);
    pen.setStyle(Qt::DashDotLine);
    painter->setPen(pen);
    painter->drawRect(rectangle);

}

int RectangleComponent::isPointAtCorner(QPointF point)
{
    int x=point.x();
    int y=point.y();
    int x1,y1,x2,y2;
    this->rectangle.getCoords(&x1,&y1,&x2,&y2);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(x1+i==x && y1+j==y) return 1;
        }
    }

    for(int i=-10;i<0;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(x2+i==x && y1+j==y) return 2;
        }
    }

    for(int i=-10;i<0;i++)
    {
        for(int j=-10;j<0;j++)
        {
           if(x2+i==x && y2+j==y) return 3;
        }
    }

    for(int i=0;i<10;i++)
    {
        for(int j=-10;j<0;j++)
        {
            if(x1+i==x && y2+j==y) return 4;
        }
    }
    return 0;
}

QString RectangleComponent::getComponentName()
{
    return componentName;
}

void RectangleComponent::setComponentName( QString value)
{
    componentName = value;
}

QColor RectangleComponent::getFilledColor() const
{
    return filledColor;
}

void RectangleComponent::setFilledColor(const QColor &value)
{
    filledColor = value;
}

void RectangleComponent::drawOpaque(QPainter *painter)
{
    painter->save();
    painter->setOpacity(0.5);
    QBrush brush;
    QPainterPath path;
    QRect rectangle(this->getRectangle());
    QColor filledColor=this->getFilledColor();
    painter->setPen(this->getPen());
    if(filledColor=="None")
    {
        painter->drawRect(rectangle);
    }
    else
    {
        brush.setColor(filledColor);
        brush.setStyle(Qt::SolidPattern);
        path.addRect(rectangle);
        painter->fillPath(path,brush);
        painter->drawRect(rectangle);
    }
    painter->restore();
}

bool RectangleComponent::isPointOnComponent(QPointF point)
{
       int x1,x2,y1,y2;
        rectangle.getCoords(&x1,&y1,&x2,&y2);
        if(point.x()>=x1 && point.x()<=x2 && point.y()>=y1 && point.y()<=y2) return true;
        else return false;

}

QString RectangleComponent::getComponentType()
{
    return componentType;
}

