#ifndef CIRCLECOMPONENT_H
#define CIRCLECOMPONENT_H
#include<QtGui>
#include <QMainWindow>
#include<drawablecomponents.h>

class CircleComponent: public DrawableComponents
{
public:
    CircleComponent();
    QRect getRectangle() const;
    void setRectangle(const QRect &value);

    QPen getPen() const;
    void setPen(const QPen &value);

    void draw(QPainter *painter) override;

    bool select(QPainter *painter, QPointF point) override;

    void select(QPainter *painter) override;

    void drawOpaque(QPainter *painter) override;

    bool isPointOnComponent(QPointF point) override;

    int isPointAtCorner(QPointF point);

    //QJsonObject createJsonObject() override;

    //DrawableComponents *readJsonObject(QJsonObject object) override;




    QString getComponentName() override;
    void setComponentName(QString value) override;

    QString getComponentType() override;

    QColor getFilledColor() const;
    void setFilledColor(const QColor &value);

private:
    QRect rectangle;
    QPen pen;
    QColor filledColor;
    const QString componentType="Circle";
    QString componentName;

    float distanceBetweenPoints(int x1,int y1,int x2,int y2);

};
#endif // CIRCLECOMPONENT_H
