#include "imagecomponent.h"

ImageComponent::ImageComponent(QString fileName)
{
    componentName=componentType;
    this->fileName=fileName;
    imagePixmap=new QPixmap(fileName);
    width=imagePixmap->width();
    height=imagePixmap->height();
    imagePixmap->scaled(width,height,Qt::IgnoreAspectRatio);
    imageRectangle.setX(30);
    imageRectangle.setY(150);
    imageRectangle.setWidth(width);
    imageRectangle.setHeight(height);
}


ImageComponent::ImageComponent(QPixmap *pixmap)
{
    componentName=componentType;
    imagePixmap=pixmap;
    width=imagePixmap->width();
    height=imagePixmap->height();
    imagePixmap->scaled(width,height,Qt::IgnoreAspectRatio);
    imageRectangle.setX(30);
    imageRectangle.setY(150);
    imageRectangle.setWidth(width);
    imageRectangle.setHeight(height);
}

QString ImageComponent::getFileName() const
{
    return fileName;
}

QRect ImageComponent::getImageRectangle() const
{
    return imageRectangle;
}

void ImageComponent::setImageRectangle(const QRect &value)
{
    imageRectangle = value;
}

QString ImageComponent::getComponentName()
{
    return componentName;
}

QString ImageComponent::getComponentType()
{
    return componentType;
}

bool ImageComponent::select(QPainter *painter, QPointF point)
{
    painter->save();
    int selectedX=point.x();
    int selectedY=point.y();
    QRect rectangle=imageRectangle;
    QPen pen("black");
    QBrush brush;
    brush.setStyle(Qt::BrushStyle());
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
        painter->drawRect(imageRectangle);
        painter->restore();
        return true;
    }
    painter->restore();
    return false;
}

void ImageComponent::select(QPainter *painter)
{
    painter->save();
    QRect rectangle=imageRectangle;
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
    painter->drawRect(imageRectangle);
    painter->restore();
}

void ImageComponent::draw(QPainter *painter)
{
    painter->drawPixmap(imageRectangle,*imagePixmap);
}

void ImageComponent::drawOpaque(QPainter *painter)
{
    painter->save();
    painter->setOpacity(0.6);
    painter->drawPixmap(imageRectangle,*imagePixmap);

    painter->restore();
}

void ImageComponent::setComponentName(QString name)
{
    componentName=name;
}

int ImageComponent::isPointAtCorner(QPointF point)
{
    int x=point.x();
    int y=point.y();
    int x1,y1,x2,y2;
    this->imageRectangle.getCoords(&x1,&y1,&x2,&y2);
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

bool ImageComponent::isPointOnComponent(QPointF point)
{
    int x1,x2,y1,y2;
    imageRectangle.getCoords(&x1,&y1,&x2,&y2);
    if(point.x()>=x1 && point.x()<=x2 && point.y()>=y1 && point.y()<=y2) return true;
    else return false;
}
