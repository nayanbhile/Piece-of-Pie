#include "drawingboard.h"


QPixmap DrawingBoard::getPixmap() const
{
    return *pixmap;
}

void DrawingBoard::draw(QPainter *painter)
{
    painter->setClipRect(this->rectangle);
    painter->save();

    painter->setOpacity(opacity);
    painter->drawPixmap(this->rectangle,*pixmap);
    painter->restore();
}

QIcon DrawingBoard::getIcon() const
{
    return icon;
}

void DrawingBoard::setIcon(const QIcon &value)
{
    icon = value;
}

DrawingBoard::DrawingBoard(QString imageFileName)
{
    pixmap=new QPixmap(imageFileName);
    icon.addFile(imageFileName);
}

QRect DrawingBoard::getRectangle() const
{
    return rectangle;
}

void DrawingBoard::setRectangle(const QRect &value)
{
    rectangle = value;
}

double DrawingBoard::getOpacity() const
{
    return opacity;
}

void DrawingBoard::setOpacity(double value)
{
    if(value<0) opacity=0;
    if(value>1) opacity=1;
    if(value<1 && value>0) opacity = value;
}

