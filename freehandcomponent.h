#ifndef FREEHANDCOMPONENT_H
#define FREEHANDCOMPONENT_H
#include<drawablecomponents.h>

class FreeHandComponent: public DrawableComponents
{
public:
    FreeHandComponent();
    QString getComponentName() override;
    void draw(QPainter *painter) override;
    void drawOpaque(QPainter *painter) override;
    QString getComponentType() override;
    void select(QPainter *painter) override;
    void setComponentName(QString name) override;
    bool select(QPainter *painter, QPointF point) override;

    bool isPointOnComponent(QPointF point) override;

    QPen getPen() const;
    void setPen(const QPen &value);

    QList<int> getXList() const;
    void setXList(const QList<int> &value);

    QList<int> getYList() const;
    void setYList(const QList<int> &value);

private:
    QPen pen;
    QString componentName;
    const QString componentType="Free Hand";
    QList<int> xList;
    QList<int> yList;
};

#endif // FREEHANDCOMPONENT_H
