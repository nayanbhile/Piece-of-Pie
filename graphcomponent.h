#ifndef GRAPHCOMPONENT_H
#define GRAPHCOMPONENT_H

#include <QMainWindow>
#include<drawablecomponents.h>
#include<QDebug>

class GraphComponent : public DrawableComponents
{
public:
    GraphComponent(QRect rectangle);
    // properties:
private:
    const QString componentType="Graph";
    QString componentName="Graph";
    QRect graphRectangle;
    double quadrantNumber;
    QPointF origin;
    int xScale,yScale;
    bool isScaled=true;
    QList<DrawableComponents *> componentList;




public:
    QString getComponentName() override;
    void setComponentName(QString componentName) override;
    QString getComponentType() override;
    bool isPointOnComponent(QPointF point) override;
    bool select(QPainter *painter, QPointF point) override;
    void select(QPainter *painter) override;
    void draw(QPainter *painter) override;
    void drawOpaque(QPainter *painter) override;

    void drawScales(QPainter *painter);
    void addComponent(DrawableComponents *component);
    void removeLast();

    QRect getGraphRectangle() const;
    void setGraphRectangle(const QRect &value);
    int getXScale() const;
    void setXScale(int value);
    int getYScale() const;
    void setYScale(int value);
    double getQuadrantNumber() const;
    void setQuadrantNumber(double value);
    QPointF getScaledPoint(QPointF unscaledPoint);
    QPointF getUnscaledPoint(QPointF scaledPoint);
    QList<DrawableComponents *> getComponentList() const;
    void setComponentList(const QList<DrawableComponents *> &value);
};

#endif // GRAPHCOMPONENT_H
