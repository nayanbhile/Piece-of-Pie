#ifndef IMAGECOMPONENT_H
#define IMAGECOMPONENT_H

#include <QWidget>
#include<QLabel>
#include<QLayout>
#include<drawablecomponents.h>
#include<QStackedLayout>

class ImageComponent: public DrawableComponents
{
public:
    ImageComponent(QString fileName);
    ImageComponent(QPixmap *pixmap);
private:
    const QString componentType="Image";
    QString componentName;
    QRect imageRectangle;
    QPixmap *imagePixmap;
    QString fileName;
    int width,height;

public:
    QString getComponentName() override;
    QString getComponentType() override;
    bool select(QPainter *painter, QPointF point) override;
    void select(QPainter *painter) override;
    void draw(QPainter *painter) override;
    void drawOpaque(QPainter *painter) override;
    void setComponentName(QString name) override;
    int isPointAtCorner(QPointF point);

    bool isPointOnComponent(QPointF point) override;
    QPixmap getImagePixmap() const;
    void setImagePixmap(const QPixmap &value);
    QRect getImageRectangle() const;
    void setImageRectangle(const QRect &value);
    QString getFileName() const;
};

#endif // IMAGECOMPONENT_H
