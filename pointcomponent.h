#ifndef POINTCOMPONENT_H
#define POINTCOMPONENT_H
#include<drawablecomponents.h>

class PointComponent : public DrawableComponents
{
public:
    PointComponent();

private:
    QPen pen;
    QPointF point;
    QString componentName="Point";
    const QString componentType="Point";

public:
    QString getComponentName() override;
    void setComponentName(QString componentName) override;
    QString getComponentType() override;
    bool isPointOnComponent(QPointF point) override;
    bool select(QPainter *painter, QPointF point) override;
    void select(QPainter *painter) override;
    void draw(QPainter *painter) override;
    void drawOpaque(QPainter *painter) override;
    QPen getPen() const;
    void setPen(const QPen &value);
    QPointF getPoint() const;
    void setPoint(const QPointF &value);
};

#endif // POINTCOMPONENT_H
