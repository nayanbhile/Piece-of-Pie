#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H
#include<QtGui>
#include <QMainWindow>
#include<drawablecomponents.h>

class RectangleComponent: public DrawableComponents
{
public:
    RectangleComponent();
    QRect getRectangle() const;
    void setRectangle(const QRect &value);

    QPen getPen() const;
    void setPen(const QPen &value);

  //  QJsonObject createJsonObject() override;
  //  DrawableComponents *readJsonObject(QJsonObject object) override;

    int isPointAtCorner(QPointF point);


    QString getComponentType() override;

    QString getComponentName() override;
    void setComponentName( QString value) override;

    QColor getFilledColor() const;
    void setFilledColor(const QColor &value);

private:
    QRect rectangle;
    QPen pen;
    QColor filledColor;
    void draw(QPainter *painter) override;
    bool select(QPainter *painter, QPointF point) override;
    void select(QPainter *painter) override;
    void drawOpaque(QPainter *painter) override;
    bool isPointOnComponent(QPointF point) override;
    const QString componentType="Rectangle";
    QString componentName;


};

#endif // RECTANGLECOMPONENT_H
