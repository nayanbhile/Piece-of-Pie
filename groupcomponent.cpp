#include "groupcomponent.h"


/*
QJsonObject GroupComponent::createJsonObject()
{

}

DrawableComponents *GroupComponent::readJsonObject(QJsonObject object)
{

}

*/
QString GroupComponent::getComponentType()
{
    return componentType;
}

QString GroupComponent::getComponentName()
{
    return componentName;
}

void GroupComponent::setComponentName(QString value)
{
    componentName=value;   
}

void GroupComponent::drawOpaque(QPainter *painter)
{
    painter->save();
    painter->setOpacity(0.6);
    for(int i=0;i<this->componentList->size();i++)
    {
        this->componentList->at(i)->draw(painter);
    }
    painter->restore();
}

bool GroupComponent::isPointOnComponent(QPointF point)
{
    bool found=false;
    for(int i=0;i<componentList->size();i++)
    {
        if(componentList->at(i)->isPointOnComponent(point))
        {
            found=true;
            break;
        }
    }
    return found;
}

GroupComponent::GroupComponent()
{
    componentList=new QList<DrawableComponents *>;
    componentName=componentType;
}


QList<DrawableComponents *> *GroupComponent::getComponentList() const
{
    return this->componentList;
}

void GroupComponent::setComponentList(QList<DrawableComponents *> *value)
{
    this->componentList = value;
}



void GroupComponent::draw(QPainter *painter)
{
    for(int i=0;i<this->componentList->size();i++)
    {
        this->componentList->at(i)->draw(painter);
    }

}

bool GroupComponent::select(QPainter *painter, QPointF point)
{
    bool found=false;
    for(int i=0;i<componentList->size() && found==false;i++)
    {
        found=componentList->at(i)->select(painter,point);

    }
    if(found==true) this->select(painter);
    return found;
}

void GroupComponent::select(QPainter *painter)
{
    for(int i=0;i<this->componentList->size();i++)
    {
        this->componentList->at(i)->select(painter);
    }
}

void GroupComponent::addComponent(DrawableComponents *component)
{
    this->componentList->append(component);
    /*
     QString recievedComponentType=component->getComponentType();
    if(recievedComponentType=="Straight Line")
    {
        LineComponent *tmp=(LineComponent *)component;
        LineComponent l;
        l.setLine(tmp->getLine());
        l.setLinePen(tmp->getLinePen());
        l.setComponentName(tmp->getComponentName());
        this->addComponent(&l);
        return;
    }
    if(recievedComponentType=="Free Hand")
    {
        FreeHandComponent *tmp=(FreeHandComponent*)component;
        FreeHandComponent f;
        f.setPen(tmp->getPen());
        f.setPointsList(tmp->getPointsList());
        f.setComponentName(tmp->getComponentName());
        this->addComponent(&f);
        return;
    }
    if(recievedComponentType=="Rectangle")
    {
        RectangleComponent *tmp=(RectangleComponent*)component;
        RectangleComponent r;
        r.setPen(tmp->getPen());
        r.setRectangle(tmp->getRectangle());
        r.setFilledColor(tmp->getFilledColor());
        r.setComponentName(tmp->getComponentName());
        this->addComponent(&r);
        return;
    }
    if(recievedComponentType=="Square")
    {
        SquareComponent *tmp=(SquareComponent*)component;
        SquareComponent r;
        r.setPen(tmp->getPen());
        r.setRectangle(tmp->getRectangle());
        r.setFilledColor(tmp->getFilledColor());
        r.setComponentName(tmp->getComponentName());
        this->addComponent(&r);
        return;
    }
    if(recievedComponentType=="Ellipse")
    {
        EllipseComponent *tmp=(EllipseComponent*)component;
        EllipseComponent r;
        r.setPen(tmp->getPen());
        r.setRectangle(tmp->getRectangle());
        r.setFilledColor(tmp->getFilledColor());
        r.setComponentName(tmp->getComponentName());
        this->addComponent(&r);
        return;
    }
    if(recievedComponentType=="Circle")
    {
        CircleComponent *tmp=(CircleComponent*)component;
        CircleComponent r;
        r.setPen(tmp->getPen());
        r.setRectangle(tmp->getRectangle());
        r.setFilledColor(tmp->getFilledColor());
        r.setComponentName(tmp->getComponentName());
        this->addComponent(&r);
        return;
    }
    if(recievedComponentType=="Image")
    {
        ImageComponent *tmp=(ImageComponent*)component;

        ImageComponent r("url");
        r.setComponentName(tmp->getComponentName());
        r.setImageRectangle(tmp->getImageRectangle());
        this->addComponent(&r);
        return;
    }
    if(recievedComponentType=="Group")
    {
        GroupComponent *tmp=(GroupComponent*)component;
        GroupComponent r;
        r.setComponentList(tmp->getComponentList());
        r.setComponentName(tmp->getComponentName());
        this->addComponent(&r);
        return;
    }
    */
}

void GroupComponent::updateComponent(int index, DrawableComponents *component)
{
   componentList->replace(index,component);
}

void GroupComponent::deleteComponent(int index)
{
    componentList->removeAt(index);
}


