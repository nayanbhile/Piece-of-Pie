#include "ellipsecomponent.h"
#include<math.h>
EllipseComponent::EllipseComponent()
{
    componentName=componentType;
}

QRect EllipseComponent::getRectangle() const
{
    return rectangle;
}

void EllipseComponent::setRectangle(const QRect &value)
{
    rectangle = value;
}

QPen EllipseComponent::getPen() const
{
    return pen;
}

void EllipseComponent::setPen(const QPen &value)
{
    pen = value;
}

void EllipseComponent::draw(QPainter *painter)
{
    painter->save();
    QRect rectangle(this->getRectangle());
    QPen pen(this->getPen());
    QBrush brush;
    QColor filledColor=this->getFilledColor();
    if(filledColor!="None")
    {
        brush.setColor(filledColor);
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(brush);
    }
    painter->setPen(pen);
    painter->drawEllipse(rectangle);
    painter->restore();
}

bool EllipseComponent::select(QPainter *painter, QPointF point)
{
    int selectedX=point.x();
    int selectedY=point.y();
    QRect rectangle=this->getRectangle();
    QPen pen("black");
    pen.setWidth(2);
    painter->setPen(pen);
    int x1,x2,y1,y2;
    rectangle.getCoords(&x1,&y1,&x2,&y2);
    float h,k,a,b;
    QPointF center(rectangle.center());
    h=center.x();
    k=center.y();
    a=h-x1;
    b=y1-k;
    if(isPointOnComponent(QPointF(selectedX,selectedY)))
    {
        this->draw(painter);
        painter->drawRect(h-6,y1-6,12,12);
        painter->drawRect(x2-6,k-6,12,12);
        painter->drawRect(h-6,y2-6,12,12);
        painter->drawRect(x1-6,k-6,12,12);
        pen.setColor("white");
        painter->setPen(pen);
        painter->drawRect(h-4,y1-4,8,8);
        painter->drawRect(x2-4,k-4,8,8);
        painter->drawRect(h-4,y2-4,8,8);
        painter->drawRect(x1-4,k-4,8,8);

        pen.setColor("black");
        pen.setWidth(5);
        pen.setStyle(Qt::DashDotLine);
        painter->setPen(pen);
        painter->drawEllipse(rectangle);
        return true;
    }
    return false;
}

void EllipseComponent::select(QPainter *painter)
{

    QRect rectangle=this->getRectangle();
    QPen pen("black");
    pen.setWidth(2);
    painter->setPen(pen);
    int x1,x2,y1,y2;
    rectangle.getCoords(&x1,&y1,&x2,&y2);
    float h,k,a,b;
    h=(x1+x2)/2;
    k=(y1+y2)/2;
    a=x1-h;
    b=y1-k;
    this->draw(painter);
    painter->drawRect(h-6,y1-6,12,12);
    painter->drawRect(x2-6,k-6,12,12);
    painter->drawRect(h-6,y2-6,12,12);
    painter->drawRect(x1-6,k-6,12,12);
    pen.setColor("white");
    painter->setPen(pen);
    painter->drawRect(h-4,y1-4,8,8);
    painter->drawRect(x2-4,k-4,8,8);
    painter->drawRect(h-4,y2-4-rectangle.height(),8,8);
    painter->drawRect(x1-4-rectangle.width(),k-4,8,8);

    pen.setColor("black");
    pen.setWidth(5);
    pen.setStyle(Qt::DashDotLine);
    painter->setPen(pen);
    painter->drawEllipse(rectangle);
}

void EllipseComponent::drawOpaque(QPainter *painter)
{
    painter->save();
    painter->setOpacity(0.5);
    QRect rectangle(this->getRectangle());
    QPen pen(this->getPen());
    QBrush brush;
    QColor filledColor=this->getFilledColor();
    if(filledColor!="None")
    {
        brush.setColor(filledColor);
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(brush);
    }
    painter->setPen(pen);
    painter->drawEllipse(rectangle);
    painter->restore();
}


bool EllipseComponent::isPointOnComponent(QPointF point)
{
    int x1,x2,y1,y2,x,y;
    x=point.x();
    y=point.y();
    rectangle.getCoords(&x1,&y1,&x2,&y2);
    float h,k,a,b;
    QPointF center(rectangle.center());
    h=center.x();
    k=center.y();
    a=h-x1;
    b=y1-k;
    float p= ( pow((x-h),2)/pow(a,2) ) + (pow((y-k),2)/pow(b,2));
    if(p<=1) return true;
    else return false;
}

int EllipseComponent::isPointAtCorner(QPointF point)
{
    int x=point.x();
    int y=point.y();
    int x1,y1,x2,y2,h,k;
    this->rectangle.getCoords(&x1,&y1,&x2,&y2);
    QPointF c(this->rectangle.center());
    h=c.x();
    k=c.y();

    for(int i=-5;i<5;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(h+i==x && y1+j==y) return 1;
        }
    }

    for(int i=-10;i<0;i++)
    {
        for(int j=-5;j<5;j++)
        {
            if(x2+i==x && k+j==y) return 2;
        }
    }

    for(int i=-5;i<5;i++)
    {
        for(int j=-10;j<0;j++)
        {
            if(h+i==x && y2+j==y) return 3;
        }
    }

    for(int i=0;i<10;i++)
    {
        for(int j=-5;j<5;j++)
        {
            if(x1+i==x && k+j==y) return 4;
        }
    }
    return 0;
}

QString EllipseComponent::getComponentName()
{
    return componentName;
}

void EllipseComponent::setComponentName(const QString value)
{
    componentName=value;

}

/*
QJsonObject EllipseComponent::createJsonObject()
{

    EllipseComponent *ellipseComponent=(EllipseComponent *)this;
    QPen pen=ellipseComponent->getPen();
    int r,g,b,penWidth,x1,x2,y1,y2;
    pen.color().getRgb(&r,&g,&b);
    penWidth=pen.width();
    QRect rectangle=ellipseComponent->getRectangle();
    rectangle.getCoords(&x1,&y1,&x2,&y2);


    QJsonObject jsonLine;
    jsonLine.insert("name","Ellipse");
    jsonLine.insert("penColorR",r);
    jsonLine.insert("penColorG",g);
    jsonLine.insert("penColorB",b);
    jsonLine.insert("penWidth",penWidth);
    jsonLine.insert("filledColor",ellipseComponent->getFilledColor());
    jsonLine.insert("x1",x1);
    jsonLine.insert("x2",x2);
    jsonLine.insert("y1",y1);
    jsonLine.insert("y2",y2);
    return jsonLine;
}

DrawableComponents *EllipseComponent::readJsonObject(QJsonObject object)
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

    EllipseComponent *component=new EllipseComponent;
    component->setRectangle(QRect(x1,y1,x2-x1,y2-y1));
    QPen pen;
    pen.setColor(QColor(r,g,b));
    pen.setWidth(penWidth);
    component->setPen(pen);
    component->setFilledColor(filledColor);
    return component;
}

*/





QString EllipseComponent::getComponentType()
{
    return componentType;
}

QColor EllipseComponent::getFilledColor() const
{
    return filledColor;
}

void EllipseComponent::setFilledColor(const QColor &value)
{
    filledColor = value;
}


