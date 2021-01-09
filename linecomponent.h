#ifndef LINECOMPONENT_H
#define LINECOMPONENT_H

#include<QtGui>
#include <QMainWindow>
#include<drawablecomponents.h>


class LineComponent: public DrawableComponents
{
public:
    LineComponent();
private:
    QLineF line;
    QPen linePen;
    const QString componentType="Straight Line";
    QString componentName;

    bool isPointOnComponent(QPointF point) override;

    int distanceBetweenPoints(int x1,int y1,int x2,int y2);
public:

    void draw(QPainter *p) override;
    void drawOpaque(QPainter *painter) override;
    bool select(QPainter *painter, QPointF point) override;
    void select(QPainter *painter) override;
    QLineF getLine() const;
    void setLine(const QLineF &value);
    QPen getLinePen() const;
    void setLinePen(const QPen &value);
  //  QJsonObject createJsonObject() override;
  //  DrawableComponents *readJsonObject(QJsonObject object) override;
    QString getComponentType() override;
    QString getComponentName() override;
    void setComponentName(const QString value) override;
};

#endif // LINECOMPONENT_H
