#ifndef DRAWABLECOMPONENTS_H
#define DRAWABLECOMPONENTS_H
#include<QPaintEvent>
#include<QPaintEngine>
#include<QPaintDevice>
#include<QMessageBox>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>

class DrawableComponents
{
public:
    DrawableComponents();
    virtual void draw(QPainter *painter)=0;
    virtual void drawOpaque(QPainter *painter)=0;
    virtual bool select(QPainter *painter,QPointF point)=0;
    virtual void select(QPainter *painter)=0;
    virtual QString getComponentType()=0;
    virtual QString getComponentName()=0;
    virtual void setComponentName(QString name)=0;
    virtual bool isPointOnComponent(QPointF point)=0;
   // virtual QJsonObject createJsonObject()=0;
   // virtual DrawableComponents *readJsonObject(QJsonObject object)=0;
};

#endif // DRAWABLECOMPONENTS_H
