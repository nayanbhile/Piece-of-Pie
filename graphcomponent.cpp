#include "graphcomponent.h"

GraphComponent::GraphComponent(QRect rect)
{
    graphRectangle=rect;
    origin=graphRectangle.center();
    xScale=yScale=50;
}

QList<DrawableComponents *> GraphComponent::getComponentList() const
{
    return componentList;
}

void GraphComponent::setComponentList(const QList<DrawableComponents *> &value)
{
    componentList = value;
}

double GraphComponent::getQuadrantNumber() const
{
    return quadrantNumber;
}

void GraphComponent::setQuadrantNumber(double value)
{
    int w,h,x,y;
    w=this->graphRectangle.width()/16;
    h=this->graphRectangle.height()/16;
    if(value<=0 || value>4)
    {
        origin=graphRectangle.center();
        quadrantNumber=0;
    }
    if(value==1)
    {
        x=this->graphRectangle.x()+w;
        y=this->graphRectangle.y()+this->graphRectangle.height()-h;
        this->origin=QPointF(x,y);
        quadrantNumber=1;
    }
    if(value==2)
    {
        x=this->graphRectangle.x()+this->graphRectangle.width()-w;
        y=this->graphRectangle.y()+this->graphRectangle.height()-h;
        this->origin=QPointF(x,y);
        quadrantNumber=2;
    }
    if(value==3)
    {
        x=this->graphRectangle.x()+this->graphRectangle.width()-w;
        y=this->graphRectangle.y()+h;
        this->origin=QPointF(x,y);
        quadrantNumber=3;
    }
    if(value==4)
    {
        x=this->graphRectangle.x()+w;
        y=this->graphRectangle.y()+h;
        this->origin=QPointF(x,y);
        quadrantNumber=4;
    }
    if(value==1.5)
    {
        x=this->graphRectangle.x()+(this->graphRectangle.width()/2);
        y=this->graphRectangle.y()+this->graphRectangle.height()-h;
        this->origin=QPointF(x,y);
        quadrantNumber=1.5;
    }
    if(value==2.5)
    {
        x=this->graphRectangle.x()+this->graphRectangle.width()-w;
        y=this->graphRectangle.y()+(this->graphRectangle.height()/2);
        this->origin=QPointF(x,y);
        quadrantNumber=2.5;
    }
    if(value==3.5)
    {
        x=this->graphRectangle.x()+(this->graphRectangle.width()/2);
        y=this->graphRectangle.y()+h;
        this->origin=QPointF(x,y);
        quadrantNumber=3.5;
    }
    if(value==0.5)
    {
        x=this->graphRectangle.x()+w;
        y=this->graphRectangle.y()+(this->graphRectangle.height()/2);
        this->origin=QPointF(x,y);
        quadrantNumber=0.5;
    }
}

QPointF GraphComponent::getScaledPoint(QPointF unscaledPoint)
{
    float ux,uy,sx,sy;
    ux=unscaledPoint.x()-this->origin.x();
    uy=this->origin.y()-unscaledPoint.y();
    sx=(ux/xScale);
    sy=(uy/yScale);
    return QPointF(sx,sy);
}

QPointF GraphComponent::getUnscaledPoint(QPointF scaledPoint)
{
    float ux,uy,sx,sy;
    sx=scaledPoint.x();
    sy=scaledPoint.y();
    ux=(xScale*sx)+this->origin.x();
    uy=this->origin.y()-(yScale*sy);
    return QPointF(ux,uy);
}

int GraphComponent::getYScale() const
{
    return yScale;
}

void GraphComponent::setYScale(int value)
{
    yScale = value;
}

int GraphComponent::getXScale() const
{
    return xScale;
}

void GraphComponent::setXScale(int value)
{
    xScale = value;
}

QRect GraphComponent::getGraphRectangle() const
{
    return graphRectangle;
}

void GraphComponent::setGraphRectangle(const QRect &value)
{
    graphRectangle = value;
}

QString GraphComponent::getComponentName()
{
    return this->componentName;
}

void GraphComponent::setComponentName(QString componentName)
{
    this->componentName=componentName;
}

QString GraphComponent::getComponentType()
{
    return this->componentType;
}

bool GraphComponent::isPointOnComponent(QPointF point)
{
    int x1,x2,y1,y2;
    graphRectangle.getCoords(&x1,&y1,&x2,&y2);
    if(point.x()>=x1 && point.x()<=x2 && point.y()>=y1 && point.y()<=y2) return true;
    else return false;
}

bool GraphComponent::select(QPainter *painter, QPointF point)
{
    int selectedX=point.x();
    int selectedY=point.y();
    QRect rectangle=this->getGraphRectangle();
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

void GraphComponent::select(QPainter *painter)
{
    QRect rectangle=this->getGraphRectangle();
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

void GraphComponent::draw(QPainter *painter)
{
    int x1,x2,y1,y2,h,k;

    painter->save();

    QBrush brush;
    QPainterPath path;
    QRect rectangle(this->getGraphRectangle());
    painter->setPen(QPen(6));

    brush.setColor(QColor(150, 255, 134));
    brush.setStyle(Qt::SolidPattern);
    path.addRect(rectangle);
    painter->fillPath(path,brush);
    painter->drawRect(rectangle);

    brush.setColor(QColor(0,134,0));
    painter->setPen(QPen(brush,2));
    rectangle.getCoords(&x1,&y1,&x2,&y2);

    h=this->origin.x();
    k=this->origin.y();

    int i=h,j=h;
    while(i<x2 || j>x1)
    {
        painter->drawLine(QPoint(j,y1),QPoint(j,y2));
        painter->drawLine(QPoint(i,y1),QPoint(i,y2));
        i+=xScale;
        j-=xScale;
    }
    i=j=k;
    while(i<y2 || j>y1)
    {
        painter->drawLine(QPoint(x1,j),QPoint(x2,j));
        painter->drawLine(QPoint(x1,i),QPoint(x2,i));
        i+=yScale;
        j-=yScale;
    }
    painter->setPen(QPen(Qt::black,4));
    painter->drawLine(QPoint(h,y1),QPoint(h,y2));
    painter->drawLine(QPoint(x1,k),QPoint(x2,k));
    if(isScaled) drawScales(painter);

    for(int i=0;i<componentList.size();i++)
    {
        componentList.at(i)->draw(painter);
    }

    painter->restore();
}

void GraphComponent::drawOpaque(QPainter *painter)
{
    int x1,x2,y1,y2,h,k;

    painter->save();
    painter->setOpacity(0.6);
    QBrush brush;
    QPainterPath path;
    QRect rectangle(this->getGraphRectangle());
    painter->setPen(QPen(6));

    brush.setColor(QColor(150, 255, 134));
    brush.setStyle(Qt::SolidPattern);
    path.addRect(rectangle);
    painter->fillPath(path,brush);
    painter->drawRect(rectangle);

    brush.setColor(QColor(0,134,0));
    painter->setPen(QPen(brush,2));
    rectangle.getCoords(&x1,&y1,&x2,&y2);

    h=this->origin.x();
    k=this->origin.y();
    int i=h,j=h;
    while(i<x2 || j>x1)
    {
        painter->drawLine(QPoint(j,y1),QPoint(j,y2));
        painter->drawLine(QPoint(i,y1),QPoint(i,y2));
        i+=xScale;
        j-=xScale;
    }
    i=j=k;
    while(i<y2 || j>y1)
    {
        painter->drawLine(QPoint(x1,j),QPoint(x2,j));
        painter->drawLine(QPoint(x1,i),QPoint(x2,i));
        i+=yScale;
        j-=yScale;
    }
    painter->setPen(QPen(Qt::black,4));
    painter->drawLine(QPoint(h,y1),QPoint(h,y2));
    painter->drawLine(QPoint(x1,k),QPoint(x2,k));

    painter->restore();
}

void GraphComponent::drawScales(QPainter *painter)
{
    painter->save();
    int x1,x2,y1,y2,h,k;
    painter->setPen(QPen(Qt::black,4));

    graphRectangle.getCoords(&x1,&y1,&x2,&y2);
    h=this->origin.x();
    k=this->origin.y();
    int i=h+xScale ,j=h-xScale;
    int p=1;
    while(i<x2 || j>x1)
    {

        painter->drawText(i-15,k+20,QString::number(p));
        painter->drawText(j-15,k+20,QString::number(-p));

        i+=xScale;
        j-=xScale;
        p++;
    }

    i=k+yScale;
    j=k-yScale;
    p=1;
    while(i<y2 || j>y1)
    {
        if(p<10)
        {
        painter->drawText(h-30,i+15,QString::number(-p));
        painter->drawText(h-20,j+15,QString::number(p));
        }
        else
        {
            painter->drawText(h-40,i+15,QString::number(-p));
            painter->drawText(h-30,j+15,QString::number(p));

        }
        i+=yScale;
        j-=yScale;
        p++;
    }

    painter->restore();
}

void GraphComponent::addComponent(DrawableComponents *component)
{
    componentList.append(component);
}

void GraphComponent::removeLast()
{
    if(componentList.size()!=0) componentList.removeLast();
}
