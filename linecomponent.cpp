#include "linecomponent.h"

LineComponent::LineComponent()
{
    componentName=componentType;
}

QString LineComponent::getComponentName()
{
    return componentName;
}

void LineComponent::setComponentName( QString value)
{
    componentName = value;
}

QString LineComponent::getComponentType()
{
    return componentType;
}

bool LineComponent::isPointOnComponent(QPointF point)
{
    int x1,y1,x2,y2,a,b;
    x1=line.x1()-1;
    x2=line.x2()-1;
    y1=line.y1()-1;
    y2=line.y2()-1;
    a=point.x();
    b=point.y();
    for(int i=0;i<=2;i++)
    {
        if(distanceBetweenPoints(a,b,x1,y1)+distanceBetweenPoints(a,b,x2,y2)==distanceBetweenPoints(x1,y1,x2,y2)) return true;
        x1++;
        x2++;
        y1++;
        y2++;
    }
    return false;
}

int LineComponent::distanceBetweenPoints(int x1, int y1, int x2, int y2)
{
    int p1=pow(x1-x2,2)+pow(y1-y2,2);
    return sqrt(p1);

}

void LineComponent::draw(QPainter *painter)
{
    painter->save();
    QPen pen(this->getLinePen());
    QLineF line(this->getLine());
    painter->setPen(pen);
    painter->drawLine(line);
    painter->restore();
}

void LineComponent::drawOpaque(QPainter *painter)
{
    painter->save();
    painter->setOpacity(0.5);
    QPen pen(this->getLinePen());
    QLineF line(this->getLine());
    painter->setPen(pen);
    painter->drawLine(line);

    painter->restore();
}

bool LineComponent::select(QPainter *painter, QPointF point)
{
    QLineF line(this->getLine());
    QPen pen("black");
    pen.setWidth(2);
    painter->setPen(pen);
    int x1,x2,y1,y2;
    x1=line.x1();
    x2=line.x2();
    y1=line.y1();
    y2=line.y2();
    if(isPointOnComponent(point))
    {
        this->draw(painter);
        painter->drawRect(x1-6,y1-6,12,12);
        painter->drawRect(x2-6,y2-6,12,12);
        pen.setColor("white");
        painter->setPen(pen);
        painter->drawRect(x1-4,y1-4,8,8);
        painter->drawRect(x2-4,y2-4,8,8);

        pen.setColor("red");
        pen.setWidth(3);
        pen.setStyle(Qt::DashDotLine);
        painter->setPen(pen);
        painter->drawLine(line);
        return true;
    }
    return false;
}

void LineComponent::select(QPainter *painter)
{


    QLineF line(this->getLine());
    QPen pen("black");
    pen.setWidth(2);
    painter->setPen(pen);
    int x1,x2,y1,y2;
    x1=line.x1();
    x2=line.x2();
    y1=line.y1();
    y2=line.y2();
    this->draw(painter);
    painter->drawRect(x1-6,y1-6,12,12);
    painter->drawRect(x2-6,y2-6,12,12);
    pen.setColor("white");
    painter->setPen(pen);
    painter->drawRect(x1-4,y1-4,8,8);
    painter->drawRect(x2-4,y2-4,8,8);

    pen.setColor("red");
    pen.setWidth(3);
    pen.setStyle(Qt::DashDotLine);
    painter->setPen(pen);
    painter->drawLine(line);

}


QPen LineComponent::getLinePen() const
{
    return linePen;
}

void LineComponent::setLinePen(const QPen &value)
{
    linePen = value;
}



QLineF LineComponent::getLine() const
{
    return line;
}

void LineComponent::setLine(const QLineF &value)
{
    line = value;
}

/*

QJsonObject LineComponent::createJsonObject()
{
    LineComponent *lineComponent=(LineComponent *)this;
    QPen pen=lineComponent->getLinePen();
    int r,g,b,penWidth,x1,x2,y1,y2;
    pen.color().getRgb(&r,&g,&b);
    penWidth=pen.width();
    QLine line=lineComponent->getLine();
    x1=line.x1();
    x2=line.x2();
    y1=line.y1();
    y2=line.y2();

    QJsonObject jsonLine;
    jsonLine.insert("name","Straight Line");
    jsonLine.insert("penColorR",r);
    jsonLine.insert("penColorG",g);
    jsonLine.insert("penColorB",b);
    jsonLine.insert("penWidth",penWidth);
    jsonLine.insert("x1",x1);
    jsonLine.insert("x2",x2);
    jsonLine.insert("y1",y1);
    jsonLine.insert("y2",y2);
    return jsonLine;
}


DrawableComponents *LineComponent::readJsonObject(QJsonObject object)
{
    int r,g,b,penWidth,x1,x2,y1,y2;
    x1=object.take("x1").toInt();
    y1=object.take("y1").toInt();
    x2=object.take("x2").toInt();
    y2=object.take("y2").toInt();
    r=object.take("penColorR").toInt();
    g=object.take("penColorG").toInt();
    b=object.take("penColorB").toInt();
    penWidth=object.take("penWidth").toInt();
    LineComponent *component=new LineComponent;
    component->setLine(QLine(x1,y1,x2,y2));
    QPen pen;
    pen.setColor(QColor(r,g,b));
    pen.setWidth(penWidth);
    component->setLinePen(pen);
    return component;

}

*/
