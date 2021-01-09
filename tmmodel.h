#ifndef TMMODEL_H
#define TMMODEL_H
#include<drawablecomponents.h>
#include<groupcomponent.h>
#include<QList>
#include<QWidget>
#include<QtGui>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<linecomponent.h>
#include<drawingboard.h>

class TMModel
{
public:
    TMModel();
    ~TMModel();

private:
    QList<DrawableComponents *> *componentList;
    QList<GroupComponent *> *groupComponentList;
    QList<QString> activityLog;
    QList<DrawableComponents *> addedList;
    QList<DrawableComponents *> redoList;
    QList<DrawableComponents *> deletedList;
    QList<QString> *tmpComponentNameList;
    QList<DrawingBoard *> *drawingBoardList;
    QList<QIcon> drawingBoardIconList;
    int lastLayer;

    QList<GroupComponent *> *tmpGroupComponentList;


public:

    void addComponent(DrawableComponents *component);
    void updateComponent(int index,DrawableComponents *updatedComponent);
    void deleteComponent(int index);
    QString getComponentNameByIndex(int index);
    QString getComponentTypeByIndex(int index);
    QList<QString> getComponentNameList();
    DrawableComponents *getComponentByIndex(int index);
    DrawableComponents *getComponentByPoint(QPointF point);
    int getComponentIndexNumber(DrawableComponents *component);

    void addGroupComponent(GroupComponent *);
    void updateGroupComponent(int index, GroupComponent *updatedGroupComponent);
    void deleteGroupComponent(int index);
    GroupComponent *getGroupComponentByIndex(int index);

    void saveComponents(QString path);
    void loadComponents(QString fileName);

    void viewAll(QPainter *painter);
    void viewTransparent(QPainter *painter);
    void populateDrawingBoards(QRect rectangle);
    void drawDrawingBoard(int index, QPainter *painter);
    void clearDrawing();
    void undoActivity();
    void redoActivity();
    int selectByPoint(QPainter *painter,QPointF selectedPoint);
    void selectByLayer(QPainter *painter,int index);
    QList<GroupComponent *> *getGroupComponentList() const;
    void setGroupComponentList(QList<GroupComponent *> *value);
    QList<QString> getActivityLog() const;
    void setActivityLog(const QList<QString> &value);
    QList<DrawableComponents *> getAddedList() const;
    void setAddedList(const QList<DrawableComponents *> &value);
    QList<DrawableComponents *> getDeletedList() const;
    void setDeletedList(const QList<DrawableComponents *> &value);
    QList<QIcon> getDrawingBoardIconList() const;
    void setDrawingBoardIconList(const QList<QIcon> &value);
    QList<DrawableComponents *> *getComponentList() const;
};

#endif // TMMODEL_H
