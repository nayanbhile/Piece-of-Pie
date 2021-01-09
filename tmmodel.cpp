#include "tmmodel.h"

TMModel::TMModel()
{
    componentList=new QList<DrawableComponents *>;
    tmpComponentNameList=new QList<QString>;
    groupComponentList=new QList<GroupComponent *>;
    tmpGroupComponentList=new QList<GroupComponent *>;
    drawingBoardList=new QList<DrawingBoard *>;
    lastLayer=0;
}

TMModel::~TMModel()
{
    delete componentList;
}

QList<DrawableComponents *> *TMModel::getComponentList() const
{
    return componentList;
}

QList<QIcon> TMModel::getDrawingBoardIconList() const
{
    return drawingBoardIconList;
}

void TMModel::setDrawingBoardIconList(const QList<QIcon> &value)
{
    drawingBoardIconList = value;
}

QList<DrawableComponents *> TMModel::getDeletedList() const
{
    return deletedList;
}

void TMModel::setDeletedList(const QList<DrawableComponents *> &value)
{
    deletedList = value;
}

QList<DrawableComponents *> TMModel::getAddedList() const
{
    return addedList;
}

void TMModel::setAddedList(const QList<DrawableComponents *> &value)
{
    addedList = value;
}

QList<QString> TMModel::getActivityLog() const
{
    return activityLog;
}

void TMModel::setActivityLog(const QList<QString> &value)
{
    activityLog = value;
}

QList<GroupComponent *> *TMModel::getGroupComponentList() const
{
    return groupComponentList;
}

void TMModel::setGroupComponentList(QList<GroupComponent *> *value)
{
    groupComponentList = value;
}


void TMModel::addComponent(DrawableComponents *d)
{
    this->componentList->append(d);
    this->addedList.append(d);
    this->activityLog.append("Added component: "+d->getComponentName());
}


QString TMModel::getComponentNameByIndex(int index)
{
    QString name=this->componentList->at(index)->getComponentName();
    return name;
}

QString TMModel::getComponentTypeByIndex(int index)
{
    QString name=this->componentList->at(index)->getComponentType();
    return name;
}

QList<QString> TMModel::getComponentNameList()
{
    QList<QString> nameList;
    for(int i=0;i<componentList->size();i++) nameList.append(componentList->at(i)->getComponentName());
    return nameList;
}

DrawableComponents *TMModel::getComponentByIndex(int index)
{
    DrawableComponents *d=this->componentList->at(index);
    return d;
}

DrawableComponents *TMModel::getComponentByPoint(QPointF point)
{
    int i;
    for(i=componentList->size()-1;i>=0;i--)
    {
        if(componentList->at(i)->isPointOnComponent(point)) return componentList->at(i);
    }
    return nullptr;
}

int TMModel::getComponentIndexNumber(DrawableComponents *component)
{
    int i;
    for(i=0;i<componentList->size();i++)
    {
        if(componentList->at(i)==component) return i;
    }
    return -1;
}

void TMModel::addGroupComponent(GroupComponent *component)
{
    this->groupComponentList->append(component);
}

void TMModel::updateGroupComponent(int index, GroupComponent *updatedGroupComponent)
{
    this->groupComponentList->replace(index,updatedGroupComponent);
}

void TMModel::updateComponent(int index, DrawableComponents *updatedComponent)
{
    this->componentList->replace(index,updatedComponent);
}

void TMModel::deleteComponent(int index)
{
    this->activityLog.append("Deleted component: "+this->componentList->at(index)->getComponentName());
    this->deletedList.append(this->componentList->at(index));
    this->componentList->removeAt(index);
}

void TMModel::deleteGroupComponent(int index)
{
    this->groupComponentList->removeAt(index);
}

GroupComponent *TMModel::getGroupComponentByIndex(int index)
{
    GroupComponent *g=this->groupComponentList->at(index);
    return g;
}




void TMModel::viewAll(QPainter *painter)
{
    DrawableComponents *d;
    for(int i=0;i<this->componentList->size();i++)
    {
        d=this->componentList->at(i);
        d->draw(painter);
    }
}

void TMModel::viewTransparent(QPainter *painter)
{
    DrawableComponents *d;
    for(int i=0;i<this->componentList->size();i++)
    {
        d=this->componentList->at(i);
        d->drawOpaque(painter);
    }
}

void TMModel::populateDrawingBoards(QRect rectangle)
{

    DrawingBoard *board;
    for(int i=0;i<=5;i++)
    {
    board=new DrawingBoard("DrawingBoards\\DrawingBoard"+QString::number(i+1)+".png");
    board->setOpacity(0.8);
    board->setRectangle(rectangle);
    drawingBoardList->append(board);
    drawingBoardIconList.append(board->getIcon());
    }

}

void TMModel::drawDrawingBoard(int index, QPainter *painter)
{
    this->drawingBoardList->at(index)->draw(painter);
}

void TMModel::clearDrawing()
{
    deletedList.clear();
    for(int i=0;i<this->componentList->size();i++)
    {
        deletedList.append(this->componentList->at(i));
    }
    this->activityLog.append("Drawing cleared");
    this->componentList->clear();

}

void TMModel::undoActivity()
{
    QString lastActivity;
    if(activityLog.size()!=0) lastActivity=this->activityLog.last();
    if(lastActivity.contains("Added") && this->addedList.size()!=0)
    {
        this->redoList.append(this->componentList->last());
        this->componentList->removeLast();
        this->addedList.removeLast();
        this->activityLog.removeLast();

    }
    if(lastActivity.contains("Deleted") && this->deletedList.size()!=0)
    {
        this->componentList->append(this->deletedList.last());
        this->redoList.append(this->deletedList.last());
        this->activityLog.append("Restored component: "+this->deletedList.last()->getComponentName());
        this->deletedList.removeLast();
    }
    if(lastActivity.contains("cleared") && this->deletedList.size()!=0)
    {
        for(int i=0;i<deletedList.size();i++)
        {
            this->componentList->append(this->deletedList.at(i));
        }
        this->activityLog.append("Restored drawing");
        this->deletedList.clear();
    }
}

void TMModel::redoActivity()
{
    if(this->redoList.size()!=0)
    {
        this->componentList->append(redoList.last());
        activityLog.append("Restored component: "+redoList.last()->getComponentName());
        redoList.removeLast();
    }
}



int TMModel::selectByPoint(QPainter *painter, QPointF selectedPoint)
{
    bool found=false;
    DrawableComponents *d;
    for(int i=this->componentList->size()-1;i>=0;i--)
    {
        d=this->componentList->at(i);
        found=d->select(painter,selectedPoint);
        if(found==true)
        {
            return i;
        }
    }
    return -1;
}

void TMModel::selectByLayer(QPainter *painter, int index)
{
    DrawableComponents *d=this->componentList->at(index);
    d->select(painter);
}

/*
void TMModel::saveComponents(QString path)
{
    QJsonArray *componentsArray=new QJsonArray();
    for(int i=0;i<this->componentList->size();i++)
    {
        componentsArray->append(this->componentList->at(i)->createJsonObject());
    }
    QFile d(path);
    d.resize(0);
    d.reset();
    d.open(QFile::ReadWrite);
    QJsonDocument doc(*componentsArray);
    d.write(doc.toJson());
    d.close();
}

void TMModel::loadComponents(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox m;
        m.setWindowTitle("ERROR!");
        m.setText("File not found");
        m.exec();
    }
    QTextStream fileReader(&file);
    QString jsonString=fileReader.readAll();
    file.close();
    QByteArray jsonBytes=jsonString.toLocal8Bit();

    auto jsonDocument=QJsonDocument::fromJson(jsonBytes);
    if(jsonDocument.isNull())
    {
        QMessageBox m;
        m.setWindowTitle("ERROR!");
        m.setText("Failed to create Json Document");
        m.exec();
        exit(2);
    }
    if(!jsonDocument.isArray())
    {
        QMessageBox m;
        m.setWindowTitle("ERROR!");
        m.setText("Json Document is not an array");
        m.exec();
        exit(3);
    }
    QJsonArray jsonArray=jsonDocument.array();
    if(jsonArray.isEmpty())
    {
        QMessageBox m;
        m.setWindowTitle("ERROR!");
        m.setText("Json Array is empty");
        m.exec();
        exit(4);
    }
    for(int i=0;i<jsonArray.size();i++)
    {
        QJsonValue jsonValue=jsonArray.at(i);
        QJsonObject jsonObject=jsonValue.toObject();
        QString name=jsonObject.take("name").toString();
        if(name=="Straight Line")
        {
            LineComponent *tmpComponent=new LineComponent;
            DrawableComponents *component=tmpComponent->readJsonObject(jsonObject);
            this->addComponent(component,"Straight Line");
        }
        if(name=="Rectangle")
        {
            RectangleComponent *tmpComponent=new RectangleComponent;
            DrawableComponents *component=tmpComponent->readJsonObject(jsonObject);
            this->addComponent(component,"Rectangle");
        }
        if(name=="Ellipse")
        {
            EllipseComponent *tmpComponent=new EllipseComponent;
            DrawableComponents *component=tmpComponent->readJsonObject(jsonObject);
            this->addComponent(component,"Ellipse");
        }
        if(name=="Free Hand")
        {
            FreeHandComponent *tmpComponent=new FreeHandComponent;
            DrawableComponents *component=tmpComponent->readJsonObject(jsonObject);
            this->addComponent(component,"Free Hand");
        }

    }

}
*/
