#ifndef GROUPCOMPONENT_H
#define GROUPCOMPONENT_H
#include<QtGui>
#include <QMainWindow>
#include<drawablecomponents.h>
#include<QList>
#include<linecomponent.h>
#include<rectanglecomponent.h>
#include<squarecomponent.h>
#include<ellipsecomponent.h>
#include<circlecomponent.h>
#include<freehandcomponent.h>
#include<imagecomponent.h>

class GroupComponent: public DrawableComponents
{
private:
    QList<DrawableComponents *> *componentList;
    const QString componentType="Group";
    QString componentName;

public:
    GroupComponent();
    void draw(QPainter *painter) override;
    bool select(QPainter *painter, QPointF point) override;
    void select(QPainter *painter) override;
    QString getComponentName() override;
    QString getComponentType() override;
    void setComponentName(QString name) override;
    void drawOpaque(QPainter *painter) override;
    bool isPointOnComponent(QPointF point) override;

    void addComponent(DrawableComponents *component);
    void updateComponent(int index, DrawableComponents *component);
    void deleteComponent(int index);
    QList<DrawableComponents *> *getComponentList() const;
    void setComponentList(QList<DrawableComponents *> *value);

   // QJsonObject createJsonObject() override;
  //  DrawableComponents *readJsonObject(QJsonObject object) override;


};

#endif // GROUPCOMPONENT_H
