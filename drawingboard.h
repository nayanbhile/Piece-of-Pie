#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H
#include<QPixmap>
#include<QPaintEvent>
#include<QPaintEngine>
#include<QPaintDevice>
#include<QIcon>
class DrawingBoard
{
public:
    DrawingBoard(QString imageFileName);

    QRect getRectangle() const;
    void setRectangle(const QRect &value);

    double getOpacity() const;
    void setOpacity(double value);

    QPixmap getPixmap() const;

    void draw(QPainter *painter);

    QIcon getIcon() const;
    void setIcon(const QIcon &value);

private:
    const  QPixmap *pixmap;
    QRect rectangle;
    double opacity;
    QIcon icon;

};

#endif // DRAWINGBOARD_H
