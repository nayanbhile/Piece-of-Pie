#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPaintDevice>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->statusbar->hide();
    modelList=new QList<TMModel *>;
    currentPageIndex=-1;
    model=new TMModel;
    modelList->append(model);
    currentPageIndex=modelList->size()-1;
    populateMainWindow();

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateMainWindow()
{
    paintFlag="";
    initialX=initialY=finalX=finalY=doubleClickedLayerIndex=selectedLayerIndex=-1;
    rectangleCorner=ellipseCorner=drawingBoardIndex=0;
    triggerReleased=selectTrigger=resizeTrigger=controlKeyPressed=false;


    layerList=new QStringList;
    this->ui->layersList->verticalHeader()->setVisible(false);
    this->ui->layersList->horizontalHeader()->setVisible(false);
    this->ui->graphPopUpFrame->setVisible(false);
    this->ui->graphPointFrame->setVisible(false);
    this->ui->graphLineFrame->setVisible(false);
    this->ui->graphEllipseFrame->setVisible(false);

    this->ui->layersList->setColumnCount(1);
    this->ui->layersList->setColumnWidth(0,261);


    int x,y,width,height;
    x=this->ui->drawingFrame->x();
    y=this->ui->drawingFrame->y();
    width=this->ui->drawingFrame->width();
    height=this->ui->drawingFrame->height();
    QRect rect(x,y,width,height);
    model->populateDrawingBoards(rect);
    QList<QIcon> tmp=model->getDrawingBoardIconList();
    this->ui->drawingBoardComboBox->clear();
    for(int i=0;i<tmp.size();i++)
    {
        this->ui->drawingBoardComboBox->addItem(tmp.at(i),nullptr);
        this->ui->drawingBoardComboBox->setModelColumn(0);
        this->ui->drawingBoardComboBox->model()->setData(ui->drawingBoardComboBox->model()->index(i, 0), QSize(200, 150), Qt::SizeHintRole);
        this->ui->drawingBoardComboBox->model()->setData(ui->drawingBoardComboBox->model()->index(i, 1), QSize(1, 150), Qt::MinimumSize);

    }
    this->ui->drawingBoardComboBox->setCurrentIndex(0);

    QPixmap cursorPixmap("icons\\defaultCursor.png");
    cursorPixmap.setDevicePixelRatio(1.5);
    QCursor defaultCursor(cursorPixmap,3,0);
    this->QWidget::setCursor(defaultCursor);
    this->ui->graphLineFrame->setCursor(defaultCursor);
    this->ui->graphPointFrame->setCursor(defaultCursor);
    this->ui->graphEllipseFrame->setCursor(defaultCursor);
    this->ui->graphPopUpFrame->setCursor(defaultCursor);
    setIcons();
    updateLayerList();

}



void MainWindow::setIcons()
{
    this->ui->color2NullButton->setIcon(QIcon("icons\\reverseBWIcon.png"));
    this->ui->imageButton->setIcon(QIcon("icons\\insertImageButtonIcon.png"));
    this->ui->openButton->setIcon(QIcon("icons\\addFileIcon.png"));
    this->ui->saveButton->setIcon(QIcon("icons\\saveFileIcon.png"));
    this->ui->saveAsButton->setIcon(QIcon("icons\\saveAsFileIcon.png"));
    this->ui->redoButton->setIcon(QIcon("icons\\redoIcon.png"));
    this->ui->undoButton->setIcon(QIcon("icons\\undoIcon.png"));
    this->ui->straightLineButton->setIcon(QIcon("icons\\lineIcon.png"));
    this->ui->freeHandButton->setIcon(QIcon("icons\\freeHandButtonIcon.png"));
    this->ui->circleButton->setIcon(QIcon("icons\\circleIcon.png"));
    this->ui->ellipseButton->setIcon(QIcon("icons\\ellipseIcon.png"));
    this->ui->squareButton->setIcon(QIcon("icons\\squareIcon.png"));
    this->ui->rectangleButton->setIcon(QIcon("icons\\rectangleIcon.png"));
    this->ui->createGroupButton->setIcon(QIcon("icons\\createGroupIcon.png"));
    this->ui->selectButton->setIcon(QIcon("icons\\selectIcon.png"));
    this->ui->clearButton->setIcon(QIcon("icons\\clearIcon.png"));
    this->ui->deleteButton->setIcon(QIcon("icons\\deleteIcon.png"));
    this->ui->deleteButton_2->setIcon(QIcon("icons\\calculatorIcon.png"));
    this->ui->addNewPageButton->setIcon(QIcon("icons\\addPageIcon.png"));
    this->ui->deletePageButton->setIcon(QIcon("icons\\deletePageIcon.png"));
    this->ui->graphLineButton->setIcon(QIcon("icons\\lineBWIcon.png"));
    this->ui->graphUndoButton->setIcon(QIcon("icons\\reverseBWIcon.png"));
    this->ui->graphEllipseButton->setIcon(QIcon("icons\\circleBWIcon.png"));
    this->ui->graphLocatorButton->setIcon(QIcon("icons\\pointBWIcon.png"));
    this->ui->graphButton->setIcon(QIcon("icons\\graphIcon.png"));
    this->ui->graphDrawGraphButton->setIcon(QIcon("icons\\drawGraphIcon.png"));
    this->ui->graphLineP1Locator->setIcon(QIcon("icons\\locatorIcon.png"));
    this->ui->graphLineP2Locator->setIcon(QIcon("icons\\locatorIcon.png"));
    this->ui->graphPointLocatorButton->setIcon(QIcon("icons\\locatorIcon.png"));
    this->ui->graphEllipseCenterLocateButton->setIcon(QIcon("icons\\locatorIcon.png"));
    this->ui->graphPointLocateButton->setIcon(QIcon("icons\\drawPointIcon.png"));
    this->ui->graphLineDrawButton->setIcon(QIcon("icons\\drawLineIcon.png"));
    this->ui->graphLineLocatorButton->setIcon(QIcon("icons\\lineBWIcon.png"));
    this->ui->graphEllipseDrawButton->setIcon(QIcon("icons\\drawEllipseIcon.png"));
    this->ui->graphEllipseLocateButton->setIcon(QIcon("icons\\circleBWIcon.png"));

    QRect rect=this->ui->logoLabel->geometry();
    QPixmap map("SplashScreen\\PieceOfPieSmallLogo.png",nullptr);
    map=map.scaled(rect.width(),rect.height(),Qt::KeepAspectRatio);
    this->ui->logoLabel->setPixmap(map);

    this->ui->color1Button->setStyleSheet("background-color: black");
}

void MainWindow::setCursor()
{
    if(paintFlag=="Free Hand")
    {
    QPixmap pencilPixmap("icons\\pencilIcon.png");
    pencilPixmap.setDevicePixelRatio(2);
    QCursor pencilCursor(pencilPixmap,0,32);
    this->ui->drawingFrame->setCursor(pencilCursor);
    return;
    }
    if(paintFlag=="Select")
    {
        if(rectangleCorner==0 && ellipseCorner==0)
        {
        QPixmap pixmap("icons\\selectCursor.png");
        pixmap.setDevicePixelRatio(2);
        QCursor cursor(pixmap,14,6);
        this->ui->drawingFrame->QWidget::setCursor(cursor);
        }
        else
        {
            QPixmap pixmap("icons\\resizeCursor.png");
            QCursor cursor(pixmap,16,16);
            this->ui->drawingFrame->QWidget::setCursor(cursor);
        }
        return;
    }
    if(paintFlag=="Graph" && graphLocator==true)
    {
        QPixmap pointPixmap("icons\\pointIcon.png");
        pointPixmap.setDevicePixelRatio(1);
        QCursor pointCursor(pointPixmap,8,10);
        this->ui->drawingFrame->setCursor(pointCursor);
        return;
    }
    if(paintFlag=="")
    {
        QPixmap cursorPixmap("icons\\defaultCursor.png");
        cursorPixmap.setDevicePixelRatio(1.5);
        QCursor defaultCursor(cursorPixmap,3,0);
        this->QWidget::setCursor(defaultCursor);
        return;
    }
    // finally
    QPixmap pixmap("icons\\drawCursor.png");
    QCursor cursor(pixmap,8,8);
    this->ui->drawingFrame->QWidget::setCursor(cursor);
}

void MainWindow::resetValues()
{
    paintFlag="";
    initialX=initialY=finalX=finalY=doubleClickedLayerIndex=selectedLayerIndex=-1;
    rectangleCorner=ellipseCorner=drawingBoardIndex=0;
    triggerReleased=selectTrigger=resizeTrigger=controlKeyPressed=false;
    layerList=new QStringList;
    this->ui->layersList->verticalHeader()->setVisible(false);
    this->ui->layersList->horizontalHeader()->setVisible(false);

    this->ui->layersList->setColumnCount(1);
    this->ui->layersList->setColumnWidth(0,261);
    setCursor();
    updateLayerList();


}

void MainWindow::paintEvent(QPaintEvent *event)
{
    setCursor();
    if(modelList->size()==0) return;

    QPainter painter(this);
    painter.setClipRect(this->ui->drawingFrame->rect());
    setFrameBackground(&painter,drawingBoardIndex);
    if(paintFlag=="Select" || paintFlag=="Group") model->viewTransparent(&painter);
    else model->viewAll(&painter);
    QPen pen;

    if(paintFlag=="Text" && pointOnDrawingBoard(QPointF(finalX,finalY)))
    {
        int x,y,width,height;
        QRect rectangle(QPoint(initialX,initialY),QPoint(finalX,finalY));
        pen.setStyle(Qt::DashDotLine);
        painter.setPen(pen);
        painter.drawRect(rectangle);
        x=rectangle.x();
        y=rectangle.y();
        width=rectangle.width();
        height=rectangle.height();
        QString displayText="Hello";
        if(triggerReleased==true) painter.drawText(x,y,width,height,Qt::AlignLeft | Qt::AlignTop, displayText);

        /*
        QRect rectangle(QPointF(initialX,initialY),QPointF(finalX,finalY));
        pen.setColor(QColor(0,0,0));
        pen.setWidth(10);
        painter.setPen(pen);
        painter.drawRect(rectangle);
        */

        if(triggerReleased==true && false)
        {
            rectangleComponent=new RectangleComponent;
            rectangleComponent->setFilledColor(color2);
            rectangleComponent->setPen(pen);
            rectangleComponent->setRectangle(rectangle);
            model->addComponent(rectangleComponent);
            updateLayerList();
            triggerReleased=false;
        }
    }

    if(paintFlag=="Straight Line" && pointOnDrawingBoard(QPointF(finalX,finalY)))
    {
        QPointF initialPoint(initialX,initialY);
        QPointF finalPoint(finalX,finalY);
        pen.setWidth(this->ui->width->value());
        pen.setColor(color1);
        painter.setPen(pen);
        painter.drawLine(initialPoint,finalPoint);

        if(triggerReleased==true)
        {
            lineComponent=new LineComponent;
            pen.setWidth(this->ui->width->value());
            pen.setColor(color1);
            lineComponent->setLinePen(pen);
            lineComponent->setLine(QLineF(initialPoint,finalPoint));
            model->addComponent(lineComponent);
            updateLayerList();
            triggerReleased=false;
        }
    }
    if(paintFlag=="Rectangle" && pointOnDrawingBoard(QPointF(finalX,finalY)))
    {
        QBrush brush;
        QPainterPath path;
        QRect rectangle(QPoint(initialX,initialY),QPoint(finalX,finalY));

        pen.setWidth(this->ui->width->value());
        pen.setColor(color1);
        painter.setPen(pen);
        if(color2!=nullptr)
        {
            brush.setColor(color2);
            brush.setStyle(Qt::SolidPattern);
            path.addRect(rectangle);
            painter.fillPath(path,brush);
        }
            painter.drawRect(rectangle);

        if(triggerReleased==true)
        {
            rectangleComponent=new RectangleComponent;
            rectangleComponent->setFilledColor(color2);
            rectangleComponent->setPen(pen);
            rectangleComponent->setRectangle(rectangle);
            model->addComponent(rectangleComponent);
            updateLayerList();
            triggerReleased=false;
        }
    }

    if(paintFlag=="Square" && pointOnDrawingBoard(QPointF(finalX,finalY)))
    {
        int dx,dy;
        dx=finalX-initialX;
        dy=finalY-initialY;
        QBrush brush;
        QPainterPath path;
        QRect rectangle;
        if((dx)>(dy)) rectangle.setRect(initialX,initialY,dx,dx);
        else rectangle.setRect(initialX,initialY,dy,dy);
        pen.setWidth(this->ui->width->value());
        pen.setColor(color1);
        painter.setPen(pen);
        if(color2!=nullptr)
        {
            brush.setColor(color2);
            brush.setStyle(Qt::SolidPattern);
            path.addRect(rectangle);
            painter.fillPath(path,brush);
        }
        painter.drawRect(rectangle);

        if(triggerReleased==true)
        {
            squareComponent=new SquareComponent;
            squareComponent->setFilledColor(color2);
            squareComponent->setPen(pen);
            squareComponent->setRectangle(rectangle);
            model->addComponent(squareComponent);
            updateLayerList();
            triggerReleased=false;
        }


    }

    if(paintFlag=="Ellipse" && pointOnDrawingBoard(QPointF(finalX,finalY)))
    {
        QBrush brush;
        QPoint initialPoint(initialX,initialY);
        QPoint finalPoint(finalX,finalY);
        QRect rectangle(initialPoint,finalPoint);
        if(color2!=nullptr)
        {
            brush.setColor(color2);
            brush.setStyle(Qt::SolidPattern);
            painter.setBrush(brush);
        }
        pen.setWidth(this->ui->width->value());
        pen.setColor(color1);
        painter.setPen(pen);
        painter.drawEllipse(rectangle);


        if(triggerReleased==true)
        {
            ellipseComponent=new EllipseComponent;
            ellipseComponent->setPen(pen);
            ellipseComponent->setRectangle(rectangle);
            ellipseComponent->setFilledColor(color2);
            model->addComponent(ellipseComponent);
            updateLayerList();
            triggerReleased=false;
        }

    }

    if(paintFlag=="Circle" && pointOnDrawingBoard(QPointF(finalX,finalY)))
    {
        int dx,dy;
        dx=finalX-initialX;
        dy=finalY-initialY;
        QBrush brush;
        QPointF initialPoint(initialX,initialY);
        QPointF finalPoint(finalX,finalY);
        QRect rectangle;
        if((dx)>(dy)) rectangle.setRect(initialX,initialY,dx,dx);
        else rectangle.setRect(initialX,initialY,dy,dy);
        if(color2!=nullptr)
        {
            brush.setColor(color2);
            brush.setStyle(Qt::SolidPattern);
            painter.setBrush(brush);
        }
        pen.setWidth(this->ui->width->value());
        pen.setColor(color1);
        painter.setPen(pen);
        painter.drawEllipse(rectangle);


        if(triggerReleased==true)
        {
            circleComponent=new CircleComponent;
            circleComponent->setPen(pen);
            circleComponent->setRectangle(rectangle);
            circleComponent->setFilledColor(color2);
            model->addComponent(circleComponent);
            updateLayerList();
            triggerReleased=false;
        }
    }

    if(paintFlag=="Free Hand" && pointOnDrawingBoard(QPointF(initialX,initialY)) && pointOnDrawingBoard(QPointF(finalX,finalY)))
    {
        QPointF currentPoint(finalX,finalY);
        QPen tmpPen;
        tmpPen.setWidth(this->ui->width->value());
        tmpPen.setColor(color1);
        painter.setPen(tmpPen);
        if(triggerReleased==false)
        {
            xList.append(finalX);
            yList.append(finalY);
        }
        for(int i=1;i<xList.size();i++)
        {
            painter.drawLine(QPointF(xList.at(i-1),yList.at(i-1)),QPointF(xList.at(i),yList.at(i)));
        }
        if(triggerReleased==true && xList.size()!=0)
        {
            freeHandComponent=new FreeHandComponent;
            freeHandComponent->setPen(tmpPen);
            freeHandComponent->setXList(xList);
            freeHandComponent->setYList(yList);
            model->addComponent(freeHandComponent);
            updateLayerList();
            xList.clear();
            yList.clear();
            triggerReleased=false;
            initialX=finalX=initialY=finalY=-1;
        }

        initialX=finalX;
        initialY=finalY;

    }

    if(paintFlag=="Graph" && this->ui->layersList->rowCount()>0 && model->getComponentByIndex(0)->getComponentType()=="Graph")
    {
        graphComponent=(GraphComponent *)model->getComponentByIndex(0);
        if(graphFlag=="Line" && graphLocator==true)
        {
            QPointF initialPoint(initialX,initialY);
            QPointF finalPoint(finalX,finalY);
            pen.setWidth(5);
            pen.setColor(this->color1);

            painter.setPen(pen);
            painter.drawLine(initialPoint,finalPoint);

            if(triggerReleased==true)
            {
                lineComponent=new LineComponent;

                lineComponent->setLinePen(pen);

                lineComponent->setLine(QLineF(initialPoint,finalPoint));
                graphComponent->addComponent(lineComponent);


                QPointF tmp=graphComponent->getScaledPoint(QPointF(initialX,initialY));
                double tmpX=(double)tmp.x();
                double tmpY=(double)tmp.y();
                this->ui->graphLineP1X->setText(QString::number(tmpX,'g',3));
                this->ui->graphLineP1Y->setText(QString::number(tmpY,'g',3));
                tmp=graphComponent->getScaledPoint(QPointF(finalX,finalY));
                tmpX=(double)tmp.x();
                tmpY=(double)tmp.y();
                this->ui->graphLineP2X->setText(QString::number(tmpX,'g',3));
                this->ui->graphLineP2Y->setText(QString::number(tmpY,'g',3));

                this->ui->graphLineFrame->setVisible(true);
                updateLayerList();
                triggerReleased=false;
                graphLocator=false;
            }

        }
        if(graphFlag=="Ellipse" && graphLocator==true)
        {
            QPoint initialPoint(initialX,initialY);
            QPoint finalPoint(finalX,finalY);
            QRect rectangle(initialPoint,finalPoint);

            pen.setWidth(5);
            pen.setColor(color1);
            painter.setPen(pen);
            painter.drawEllipse(rectangle);


            if(triggerReleased==true)
            {
                ellipseComponent=new EllipseComponent;
                ellipseComponent->setPen(pen);
                ellipseComponent->setRectangle(rectangle);
                ellipseComponent->setFilledColor(color2);
                graphComponent->addComponent(ellipseComponent);

                QPointF scaledCenter=graphComponent->getScaledPoint(rectangle.center());
                this->ui->graphEllipseCenterAbscissa->setText(QString::number(scaledCenter.x(),'g',3));
                this->ui->graphEllipseCenterOrdinate->setText(QString::number(scaledCenter.y(),'g',3));
                double xScale,yScale;
                xScale=graphComponent->getXScale();
                yScale=graphComponent->getYScale();
                double scaledWidth=rectangle.width()/xScale;
                double scaledHeight=rectangle.height()/yScale;
                this->ui->graphEllipseWidth->setText(QString::number(scaledWidth/2,'g',3));
                this->ui->graphEllipseHeight->setText(QString::number(scaledHeight/2,'g',3));

                this->ui->graphEllipseFrame->setVisible(true);
                updateLayerList();
                triggerReleased=false;
                graphLocator=false;
            }

        }


    }

    if(paintFlag=="Select" && controlKeyPressed==false)
    {
        QPointF selectedPoint(initialX,initialY);
        if(selectTrigger==true && pointOnDrawingBoard(selectedPoint)) selectedLayerIndex=model->selectByPoint(&painter,selectedPoint);
        if(selectedLayerIndex!=-1) this->ui->layersList->selectRow(selectedLayerIndex);
        else if(tmpSelectedComponentList.size()==0) this->ui->layersList->selectRow(selectedLayerIndex);
        if(selectedLayerIndex!=-1 )
        {
            model->selectByLayer(&painter,selectedLayerIndex);
        }
        if(selectedLayerIndex==-1)
        {
            this->ui->layersList->clearSelection();
        }

        if(selectTrigger==false && pointOnDrawingBoard(selectedPoint) && selectedLayerIndex!=-1)
        {
            int dx,dy;
            dx=finalX-initialX;
            dy=finalY-initialY;
            DrawableComponents *d=model->getComponentByIndex(selectedLayerIndex);
            QString componentName=d->getComponentType();

            if(componentName=="Straight Line")
            {
                int x1,y1,x2,y2;
                LineComponent *l=(LineComponent*)d;
                QLineF updatedLine(l->getLine());
                x1=updatedLine.x1()+dx;
                x2=updatedLine.x2()+dx;
                y1=updatedLine.y1()+dy;
                y2=updatedLine.y2()+dy;
                updatedLine.setP1(QPointF(x1,y1));
                updatedLine.setP2(QPointF(x2,y2));
                l->setLine(updatedLine);
                model->updateComponent(selectedLayerIndex,l);
                initialX=finalX;
                initialY=finalY;
            }
            if(componentName=="Rectangle" && rectangleCorner==0)
            {
                int x=0,y=0;
                RectangleComponent *r=(RectangleComponent *)d;
                QRect updatedRectangle(r->getRectangle());
                x=updatedRectangle.x()+dx;
                y=updatedRectangle.y()+dy;
                updatedRectangle.moveTo(x,y);
                r->setRectangle(updatedRectangle);
                model->updateComponent(selectedLayerIndex,r);
                initialX=finalX;
                initialY=finalY;

            }
            if(componentName=="Ellipse" && ellipseCorner==0)
            {
                int x,y;
                EllipseComponent *e=(EllipseComponent*)d;
                QRect updatedRectangle(e->getRectangle());
                x=updatedRectangle.x()+dx;
                y=updatedRectangle.y()+dy;
                updatedRectangle.moveTo(x,y);
                e->setRectangle(updatedRectangle);
                model->updateComponent(selectedLayerIndex,e);
                initialX=finalX;
                initialY=finalY;
            }
            if(componentName=="Circle" && ellipseCorner==0)
            {
                int x,y;
                CircleComponent *e=(CircleComponent *)d;
                QRect updatedRectangle(e->getRectangle());
                x=updatedRectangle.x()+dx;
                y=updatedRectangle.y()+dy;
                updatedRectangle.moveTo(x,y);
                e->setRectangle(updatedRectangle);
                model->updateComponent(selectedLayerIndex,e);
                initialX=finalX;
                initialY=finalY;
            }
            if(componentName=="Square" && rectangleCorner==0)
            {
                int x,y;
                SquareComponent *s=(SquareComponent*)d;
                QRect updatedRectangle(s->getRectangle());
                x=updatedRectangle.x()+dx;
                y=updatedRectangle.y()+dy;
                updatedRectangle.moveTo(x,y);
                s->setRectangle(updatedRectangle);
                model->updateComponent(selectedLayerIndex,s);
                initialX=finalX;
                initialY=finalY;
            }
            if(componentName=="Free Hand")
            {
                int x,y;
                qDebug() <<"Control aya";
                FreeHandComponent *f=(FreeHandComponent*)d;
                QList<int> updatedXList(f->getXList());
                QList<int> updatedYList(f->getYList());
                for(int i=0;i<updatedXList.size();i++)
                {
                    x=updatedXList.at(i)+dx;
                    y=updatedYList.at(i)+dy;
                    updatedXList.replace(i,x);
                    updatedYList.replace(i,y);

                }
                f->setXList(updatedXList);
                f->setYList(updatedYList);
                model->updateComponent(selectedLayerIndex,f);
                initialX=finalX;
                initialY=finalY;
            }

            if(componentName=="Image" && rectangleCorner==0)
            {
                int x=0,y=0;
                ImageComponent *i=(ImageComponent *)d;
                QRect updatedRectangle(i->getImageRectangle());
                x=updatedRectangle.x()+dx;
                y=updatedRectangle.y()+dy;
                updatedRectangle.moveTo(x,y);
                i->setImageRectangle(updatedRectangle);
                model->updateComponent(selectedLayerIndex,i);
                initialX=finalX;
                initialY=finalY;
            }
            if(componentName=="Group")
            {
                GroupComponent *g=(GroupComponent *)d;
                moveTheGroup(g,dx,dy);

                model->updateComponent(selectedLayerIndex,groupComponent);
                initialX=finalX;
                initialY=finalY;
            }

        }
        if(resizeTrigger==true && pointOnDrawingBoard(selectedPoint) && selectedLayerIndex!=-1)
        {

            QString componentName=model->getComponentNameByIndex(selectedLayerIndex);

            if(componentName=="Rectangle")
            {
                RectangleComponent *d=(RectangleComponent *)model->getComponentByIndex(selectedLayerIndex);
                QRect updatedRectangle(d->getRectangle());

            if(triggerReleased==false && rectangleCorner==3)
            {
                updatedRectangle.setRight(finalX);
                updatedRectangle.setBottom(finalY);
                d->setRectangle(updatedRectangle);
                model->updateComponent(selectedLayerIndex,d);
            }
            if(triggerReleased==false && rectangleCorner==1)
            {
                updatedRectangle.setLeft(finalX);
                updatedRectangle.setTop(finalY);
                d->setRectangle(updatedRectangle);
                model->updateComponent(selectedLayerIndex,d);
            }if(triggerReleased==false && rectangleCorner==2)
            {
                updatedRectangle.setRight(finalX);
                updatedRectangle.setTop(finalY);
                d->setRectangle(updatedRectangle);
                model->updateComponent(selectedLayerIndex,d);
            }if(triggerReleased==false && rectangleCorner==4)
            {
                updatedRectangle.setLeft(finalX);
                updatedRectangle.setBottom(finalY);
                d->setRectangle(updatedRectangle);
                model->updateComponent(selectedLayerIndex,d);
            }

            initialX=finalX;
            initialY=finalY;
            }

            if(componentName=="Square")
            {
                SquareComponent *d=(SquareComponent *)model->getComponentByIndex(selectedLayerIndex);
                QRect updatedRectangle(d->getRectangle());
                int move;
                int h=updatedRectangle.center().x();
                int k=updatedRectangle.center().y();
                if(triggerReleased==false && rectangleCorner==3)
                {
                    move=(finalY-k);
                    updatedRectangle.setBottom(finalY);
                    updatedRectangle.setRight(h+move);
                   // updatedRectangle.setLeft(h-move);
                    d->setRectangle(updatedRectangle);
                    model->updateComponent(selectedLayerIndex,d);
                }
                if(triggerReleased==false && rectangleCorner==1)
                {
                    move=(k-finalY);
                    updatedRectangle.setTop(finalY);
                    updatedRectangle.setLeft(h-move);
                    //updatedRectangle.setRight(h+move);
                    d->setRectangle(updatedRectangle);
                    model->updateComponent(selectedLayerIndex,d);
                }
                if(triggerReleased==false && rectangleCorner==2)
                {
                    move=(finalX-h);
                    updatedRectangle.setRight(finalX);
                    updatedRectangle.setTop(k-move);
                   // updatedRectangle.setBottom(k+move);
                    d->setRectangle(updatedRectangle);
                    model->updateComponent(selectedLayerIndex,d);
                }
                if(triggerReleased==false && rectangleCorner==4)
                {
                    move=(h-finalX);
                    updatedRectangle.setLeft(finalX);
                    updatedRectangle.setBottom(k+move);
                    //updatedRectangle.setTop(k-move);
                    d->setRectangle(updatedRectangle);
                    model->updateComponent(selectedLayerIndex,d);
                }
            }

             if(componentName=="Ellipse")
             {
                 EllipseComponent *e=(EllipseComponent *)model->getComponentByIndex(selectedLayerIndex);
                 QRect updatedRectangle(e->getRectangle());
                 if(triggerReleased==false && ellipseCorner==3)
                 {
                     updatedRectangle.setBottom(finalY);
                     e->setRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,e);
                 }
                 if(triggerReleased==false && ellipseCorner==1)
                 {
                     updatedRectangle.setTop(finalY);
                     e->setRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,e);
                 }
                 if(triggerReleased==false && ellipseCorner==2)
                 {
                     updatedRectangle.setRight(finalX);
                     e->setRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,e);
                 }
                 if(triggerReleased==false && ellipseCorner==4)
                 {
                     updatedRectangle.setLeft(finalX);
                     e->setRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,e);
                 }
             }

             if(componentName=="Circle")
             {
                 CircleComponent *e=(CircleComponent *)model->getComponentByIndex(selectedLayerIndex);
                 QRect updatedRectangle(e->getRectangle());
                 int h=updatedRectangle.center().x();
                 int k=updatedRectangle.center().y();
                 int move;
                 if(triggerReleased==false && ellipseCorner==3)
                 {
                     move=(finalY-k);
                     updatedRectangle.setBottom(finalY);
                     updatedRectangle.setRight(h+move);
                     updatedRectangle.setLeft(h-move);
                     e->setRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,e);
                 }
                 if(triggerReleased==false && ellipseCorner==1)
                 {
                     move=(k-finalY);
                     updatedRectangle.setTop(finalY);
                     updatedRectangle.setLeft(h-move);
                     updatedRectangle.setRight(h+move);
                     e->setRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,e);
                 }
                 if(triggerReleased==false && ellipseCorner==2)
                 {
                     move=(finalX-h);
                     updatedRectangle.setRight(finalX);
                     updatedRectangle.setTop(k-move);
                     updatedRectangle.setBottom(k+move);
                     e->setRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,e);
                 }
                 if(triggerReleased==false && ellipseCorner==4)
                 {
                     move=(h-finalX);
                     updatedRectangle.setLeft(finalX);
                     updatedRectangle.setBottom(k+move);
                     updatedRectangle.setTop(k-move);
                     e->setRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,e);
                 }
             }
             if(componentName=="Image")
             {
                 ImageComponent *d=(ImageComponent *)model->getComponentByIndex(selectedLayerIndex);
                 QRect updatedRectangle(d->getImageRectangle());

                 if(triggerReleased==false && rectangleCorner==3)
                 {
                     updatedRectangle.setRight(finalX);
                     updatedRectangle.setBottom(finalY);
                     d->setImageRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,d);
                 }
                 if(triggerReleased==false && rectangleCorner==1)
                 {
                     updatedRectangle.setLeft(finalX);
                     updatedRectangle.setTop(finalY);
                     d->setImageRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,d);
                 }if(triggerReleased==false && rectangleCorner==2)
                 {
                     updatedRectangle.setRight(finalX);
                     updatedRectangle.setTop(finalY);
                     d->setImageRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,d);
                 }if(triggerReleased==false && rectangleCorner==4)
                 {
                     updatedRectangle.setLeft(finalX);
                     updatedRectangle.setBottom(finalY);
                     d->setImageRectangle(updatedRectangle);
                     model->updateComponent(selectedLayerIndex,d);
                 }

                 initialX=finalX;
                 initialY=finalY;
             }


        }

    }

    if(controlKeyPressed && paintFlag=="Select")
    {
        DrawableComponents *d;
        for(int i=0;i<tmpSelectedComponentList.size();i++)
        {
            d=tmpSelectedComponentList.at(i);
            d->select(&painter);
        }
    }

}

void MainWindow::moveTheGroup(DrawableComponents *d, int dx, int dy)
{
    GroupComponent *g=(GroupComponent *)d;
    DrawableComponents *c;
    qDebug() <<"Got g";
    for(int i=0;i<g->getComponentList()->size();i++)
    {
        qDebug() <<"For me aya";
        c=g->getComponentList()->at(i);
        QString componentName=c->getComponentType();

        if(componentName=="Straight Line")
        {
            int x1,y1,x2,y2;
            LineComponent *l=(LineComponent*)c;
            QLineF updatedLine(l->getLine());
            x1=updatedLine.x1()+dx;
            x2=updatedLine.x2()+dx;
            y1=updatedLine.y1()+dy;
            y2=updatedLine.y2()+dy;
            updatedLine.setP1(QPointF(x1,y1));
            updatedLine.setP2(QPointF(x2,y2));
            l->setLine(updatedLine);
            g->updateComponent(i,l);

        }
        if(componentName=="Rectangle" && rectangleCorner==0)
        {
            int x=0,y=0;
            RectangleComponent *r=(RectangleComponent *)c;
            QRect updatedRectangle(r->getRectangle());
            x=updatedRectangle.x()+dx;
            y=updatedRectangle.y()+dy;
            updatedRectangle.moveTo(x,y);
            r->setRectangle(updatedRectangle);
            g->updateComponent(i,r);


        }
        if(componentName=="Ellipse" && ellipseCorner==0)
        {
            int x,y;
            EllipseComponent *e=(EllipseComponent*)c;
            QRect updatedRectangle(e->getRectangle());
            x=updatedRectangle.x()+dx;
            y=updatedRectangle.y()+dy;
            updatedRectangle.moveTo(x,y);
            e->setRectangle(updatedRectangle);
            g->updateComponent(i,e);

        }
        if(componentName=="Circle" && ellipseCorner==0)
        {
            int x,y;
            CircleComponent *e=(CircleComponent *)c;
            QRect updatedRectangle(e->getRectangle());
            x=updatedRectangle.x()+dx;
            y=updatedRectangle.y()+dy;
            updatedRectangle.moveTo(x,y);
            e->setRectangle(updatedRectangle);
            g->updateComponent(i,e);

        }
        if(componentName=="Square" && rectangleCorner==0)
        {
            int x,y;
            SquareComponent *s=(SquareComponent*)c;
            QRect updatedRectangle(s->getRectangle());
            x=updatedRectangle.x()+dx;
            y=updatedRectangle.y()+dy;
            updatedRectangle.moveTo(x,y);
            s->setRectangle(updatedRectangle);
            g->updateComponent(i,s);

        }
        if(componentName=="Free Hand")
        {
            int x,y;
            qDebug() <<"Control aya";
            FreeHandComponent *f=(FreeHandComponent*)c;
            QList<int> updatedXList(f->getXList());
            QList<int> updatedYList(f->getYList());
            for(int i=0;i<updatedXList.size();i++)
            {
                x=updatedXList.at(i)+dx;
                y=updatedYList.at(i)+dy;
                updatedXList.replace(i,x);
                updatedYList.replace(i,y);

            }
            f->setXList(updatedXList);
            f->setYList(updatedYList);
            g->updateComponent(i,f);

        }

        if(componentName=="Image" && rectangleCorner==0)
        {
            int x=0,y=0;
            ImageComponent *img=(ImageComponent *)c;
            QRect updatedRectangle(img->getImageRectangle());
            x=updatedRectangle.x()+dx;
            y=updatedRectangle.y()+dy;
            updatedRectangle.moveTo(x,y);
            img->setImageRectangle(updatedRectangle);
            g->updateComponent(i,img);
        }
        if(componentName=="Group")
        {
            GroupComponent *s=(GroupComponent *)c;
            moveTheGroup(s,dx,dy);
        }
    }

}

DrawableComponents *MainWindow::getComponentCopy(DrawableComponents *d)
{
    QString componenttype=d->getComponentType();
    if(componenttype=="Straight Line")
    {
        int x1,y1,x2,y2;
        LineComponent *tmp=(LineComponent *)d;
        LineComponent *l=new LineComponent;
        QLineF line;
        x1=tmp->getLine().x1();
        y1=tmp->getLine().y1();
        x2=tmp->getLine().x2();
        y2=tmp->getLine().y2();
        line.setLine(x1,y1,x2,y2);
        l->setLine(line);
        l->setComponentName(tmp->getComponentName());
        l->setLinePen(tmp->getLinePen());
        return l;
    }
    return nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
    {
        controlKeyPressed=true;
    }
    if(event->key()==Qt::Key_Escape) QApplication::quit();
    if(event->key()==Qt::Key_T)
    {
        QMessageBox m;
        m.setText(QString::number(tmpSelectedComponentList.size()));
        m.exec();
    }
    if(event->key()==Qt::Key_Delete)
    {
        on_deleteButton_clicked();
    }
    if(controlKeyPressed && event->key()==Qt::Key_C && (selectedLayerIndex!=-1 || tmpSelectedComponentList.size()>0))
    {
        QMessageBox m;
        m.setText("CTRL+C pressed");
        m.exec();
        copiedComponentList.clear();
        if(selectedLayerIndex!=-1) copiedComponentList.append(getComponentCopy(model->getComponentByIndex(selectedLayerIndex)));
    }
    if(controlKeyPressed && event->key()==Qt::Key_V && copiedComponentList.size()>0)
    {
        QMessageBox m;
        m.setText("CTRL+V pressed");
        m.exec();
        for(int i=0;i<copiedComponentList.size();i++) model->addComponent(copiedComponentList.at(i));

        updateLayerList();
        update();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control) controlKeyPressed=false;
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(pointOnDrawingBoard(QPointF(event->x(),event->y())))
    {
        finalX=event->x();
        finalY=event->y();
        triggerReleased=false;
        update();
    }
    selectTrigger=false;

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if(pointOnDrawingBoard(QPointF(event->x(),event->y())))
    {
        initialX=event->x();
        initialY=event->y();
        finalX=initialX;
        finalY=initialY;
        selectTrigger=true;
        resizeTrigger=true;
        resizingPoint=QPointF(initialX,initialY);
        update();
        if(paintFlag=="Select" && selectedLayerIndex!=-1)
        {
        QString componentName=model->getComponentNameByIndex(selectedLayerIndex);

        if(componentName=="Rectangle")
        {
            RectangleComponent *r=(RectangleComponent*)model->getComponentByIndex(selectedLayerIndex);
            rectangleCorner=r->isPointAtCorner(QPointF(initialX,initialY));
            update();
        }
        if(componentName=="Square")
        {
            SquareComponent *r=(SquareComponent*)model->getComponentByIndex(selectedLayerIndex);
            rectangleCorner=r->isPointAtCorner(QPointF(initialX,initialY));
            update();
        }
        if(componentName=="Ellipse")
        {
            EllipseComponent *e=(EllipseComponent *)model->getComponentByIndex(selectedLayerIndex);
            ellipseCorner=e->isPointAtCorner(QPointF(initialX,initialY));
            update();
        }
        if(componentName=="Circle")
        {
            CircleComponent *e=(CircleComponent *)model->getComponentByIndex(selectedLayerIndex);
            ellipseCorner=e->isPointAtCorner(QPointF(initialX,initialY));
            update();
        }
        if(componentName=="Image")
        {
            ImageComponent *r=(ImageComponent*)model->getComponentByIndex(selectedLayerIndex);
            rectangleCorner=r->isPointAtCorner(QPointF(initialX,initialY));
            update();
        }
        }

        if(paintFlag=="Graph" && this->ui->layersList->rowCount()!=0 && model->getComponentByIndex(0)->getComponentType()=="Graph")
        {
            if(graphLocator==true && graphFlag=="Point")
            {
                graphComponent=(GraphComponent *)model->getComponentByIndex(0);
                QPointF tmp=graphComponent->getScaledPoint(QPointF(initialX,initialY));
                double tmpX=(double)tmp.x();
                double tmpY=(double)tmp.y();
                this->ui->graphPointAbscissa->setText(QString::number(tmpX,'g',2));
                this->ui->graphPointOrdinate->setText(QString::number(tmpY,'g',2));
                this->ui->graphPointFrame->setVisible(true);
            }
            if(graphLocator==true && graphFlag=="LineP1")
            {
                graphComponent=(GraphComponent *)model->getComponentByIndex(0);
                QPointF tmp=graphComponent->getScaledPoint(QPointF(initialX,initialY));
                double tmpX=(double)tmp.x();
                double tmpY=(double)tmp.y();
                this->ui->graphLineP1X->setText(QString::number(tmpX,'g',2));
                this->ui->graphLineP1Y->setText(QString::number(tmpY,'g',2));
                this->ui->graphLineFrame->setVisible(true);
            }
            if(graphLocator==true && graphFlag=="LineP2")
            {
                graphComponent=(GraphComponent *)model->getComponentByIndex(0);
                QPointF tmp=graphComponent->getScaledPoint(QPointF(initialX,initialY));
                double tmpX=(double)tmp.x();
                double tmpY=(double)tmp.y();
                this->ui->graphLineP2X->setText(QString::number(tmpX,'g',2));
                this->ui->graphLineP2Y->setText(QString::number(tmpY,'g',2));
                this->ui->graphLineFrame->setVisible(true);
            }
            if(graphLocator==true && graphFlag=="EllipseCenter")
            {
                graphComponent=(GraphComponent *)model->getComponentByIndex(0);
                QPointF tmp=graphComponent->getScaledPoint(QPointF(initialX,initialY));
                double tmpX=(double)tmp.x();
                double tmpY=(double)tmp.y();
                this->ui->graphEllipseCenterAbscissa->setText(QString::number(tmpX,'g',2));
                this->ui->graphEllipseCenterOrdinate->setText(QString::number(tmpY,'g',2));
                this->ui->graphEllipseFrame->setVisible(true);
            }

        }

        if(controlKeyPressed && paintFlag=="Select")
        {
            DrawableComponents *d=model->getComponentByPoint(QPointF(initialX,initialY));
            if(tmpSelectedComponentList.contains(d))
            {
                tmpSelectedComponentList.removeOne(d);
            }
            else if(d!=nullptr) tmpSelectedComponentList.append(d);
            this->ui->layersList->clearSelection();
            for(int i=0;i<tmpSelectedComponentList.size();i++) this->ui->layersList->selectRow(model->getComponentIndexNumber(tmpSelectedComponentList.at(i)));

        }
        if(!controlKeyPressed && pointOnDrawingBoard(QPointF(initialX,initialY)))
        {
            QPointF currentPoint(initialX,initialY);
            bool found=false;
            for(int i=0;i<tmpSelectedComponentList.size() && found==false;i++) found=tmpSelectedComponentList.at(i)->isPointOnComponent(currentPoint);
            if(!found) tmpSelectedComponentList.clear();
        }

        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(pointOnDrawingBoard(QPointF(event->x(),event->y())))
    {
        finalX=event->x();
        finalY=event->y();
        triggerReleased=true;
       // selectTrigger=true;
        resizeTrigger=false;
        update();
    }
    if(paintFlag=="Select")
    {
        rectangleCorner=0;
        ellipseCorner=0;
    }

}


void MainWindow::setFrameBackground(QPainter *painter ,int drawingBoardIndex)
{
       int x1,y1,width,height;
        x1=this->ui->drawingFrame->x();
        y1=this->ui->drawingFrame->y();
        width=this->ui->drawingFrame->width();
        height=this->ui->drawingFrame->height();
        QRect background(x1,y1,width,height);
        painter->setClipRect(background);

        QBrush brush;
        QPainterPath path;

        brush.setColor(QColor(255,255,255));
        brush.setStyle(Qt::SolidPattern);
        path.addRect(background);
        painter->fillPath(path,brush);

    model->drawDrawingBoard(drawingBoardIndex,painter);

}

bool MainWindow::pointOnDrawingBoard(QPointF point)
{
    int x1,x2,y1,y2;
    x1=this->ui->drawingFrame->x();
    x2=this->ui->drawingFrame->x()+ this->ui->drawingFrame->width();
    y1=this->ui->drawingFrame->y();
    y2=this->ui->drawingFrame->y()+ this->ui->drawingFrame->height();
    if(point.x()<x1 || point.x()>x2) return false;
    if(point.y()<y1 || point.y()>y2) return false;
    return true;
}

void MainWindow::updateLayerList()
{
    //this->ui->layersList->clear();
    //this->ui->layersList->addItems(model->getComponentNameList());

    this->ui->currentPageLineEdit->setText(QString::number(currentPageIndex+1));
    this->ui->totalPagesLabel2->setText(QString::number(modelList->size()));
    if(controlKeyPressed==false)
    {
    this->ui->layersList->clear();
    QList<QString> tmpList=model->getComponentNameList();
    this->ui->layersList->setRowCount(tmpList.size());
    for(int i=0;i<tmpList.size();i++)
    {
        this->ui->layersList->setRowHeight(i,50);
        this->ui->layersList->setItem(i,0,new QTableWidgetItem(tmpList.at(i)));
    }
    tmpList.clear();

    activityLog.clear();
    this->ui->activityLog->clear();
    activityLog=model->getActivityLog();
    this->ui->activityLog->addItems(activityLog);
    }
}

void MainWindow::setButtonsUnchecked()
{
    this->ui->straightLineButton->setChecked(false);
    this->ui->freeHandButton->setChecked(false);
    this->ui->circleButton->setChecked(false);
    this->ui->ellipseButton->setChecked(false);
    this->ui->squareButton->setChecked(false);
    this->ui->rectangleButton->setChecked(false);
    this->ui->selectButton->setChecked(false);

}

void MainWindow::moveSelectedComponent(DrawableComponents *d,int dx,int dy)
{
    QString componentName=d->getComponentType();

    if(componentName=="Straight Line")
    {
        int x1,y1,x2,y2;
        LineComponent *l=(LineComponent*)d;
        QLineF updatedLine(l->getLine());
        x1=updatedLine.x1()+dx;
        x2=updatedLine.x2()+dx;
        y1=updatedLine.y1()+dy;
        y2=updatedLine.y2()+dy;
        updatedLine.setP1(QPointF(x1,y1));
        updatedLine.setP2(QPointF(x2,y2));
        l->setLine(updatedLine);
        model->updateComponent(selectedLayerIndex,l);
        initialX=finalX;
        initialY=finalY;
    }
    if(componentName=="Rectangle" && rectangleCorner==0)
    {
        int x=0,y=0;
        RectangleComponent *d=(RectangleComponent *)d;
        QRect updatedRectangle(d->getRectangle());
        x=updatedRectangle.x()+dx;
        y=updatedRectangle.y()+dy;
        updatedRectangle.moveTo(x,y);
        d->setRectangle(updatedRectangle);
        model->updateComponent(selectedLayerIndex,d);
        initialX=finalX;
        initialY=finalY;

    }
    if(componentName=="Ellipse" && ellipseCorner==0)
    {
        int x,y;
        EllipseComponent *e=(EllipseComponent*)d;
        QRect updatedRectangle(e->getRectangle());
        x=updatedRectangle.x()+dx;
        y=updatedRectangle.y()+dy;
        updatedRectangle.moveTo(x,y);
        e->setRectangle(updatedRectangle);
        model->updateComponent(selectedLayerIndex,e);
        initialX=finalX;
        initialY=finalY;
    }
    if(componentName=="Circle" && ellipseCorner==0)
    {
        int x,y;
        CircleComponent *e=(CircleComponent *)d;
        QRect updatedRectangle(e->getRectangle());
        x=updatedRectangle.x()+dx;
        y=updatedRectangle.y()+dy;
        updatedRectangle.moveTo(x,y);
        e->setRectangle(updatedRectangle);
        model->updateComponent(selectedLayerIndex,e);
        initialX=finalX;
        initialY=finalY;
    }
    if(componentName=="Square" && rectangleCorner==0)
    {
        int x,y;
        SquareComponent *d=(SquareComponent*)d;
        QRect updatedRectangle(d->getRectangle());
        x=updatedRectangle.x()+dx;
        y=updatedRectangle.y()+dy;
        updatedRectangle.moveTo(x,y);
        d->setRectangle(updatedRectangle);
        model->updateComponent(selectedLayerIndex,d);
        initialX=finalX;
        initialY=finalY;
    }
    if(componentName=="Free Hand")
    {
        int x,y;
        qDebug() <<"Control aya";
        FreeHandComponent *f=(FreeHandComponent*)d;
        QList<int> updatedXList(f->getXList());
        QList<int> updatedYList(f->getYList());
        for(int i=0;i<updatedXList.size();i++)
        {
            x=updatedXList.at(i)+dx;
            y=updatedYList.at(i)+dy;
            updatedXList.replace(i,x);
            updatedYList.replace(i,y);

        }
        f->setXList(updatedXList);
        f->setYList(updatedYList);
        model->updateComponent(selectedLayerIndex,f);
        initialX=finalX;
        initialY=finalY;
    }

    if(componentName=="Image" && rectangleCorner==0)
    {
        int x=0,y=0;
        ImageComponent *d=(ImageComponent *)d;
        QRect updatedRectangle(d->getImageRectangle());
        x=updatedRectangle.x()+dx;
        y=updatedRectangle.y()+dy;
        updatedRectangle.moveTo(x,y);
        d->setImageRectangle(updatedRectangle);
        model->updateComponent(selectedLayerIndex,d);
        initialX=finalX;
        initialY=finalY;
    }
    if(componentName=="Group")
    {
        GroupComponent *g=(GroupComponent *)d;
        DrawableComponents *c;
        for(int i=0;i<g->getComponentList()->size();i++)
        {
            c=g->getComponentList()->at(i);
            qDebug() <<c->getComponentType();
            moveSelectedComponent(c,dx,dy);
        }
    }

}


void MainWindow::on_straightLineButton_clicked()
{

    paintFlag="Straight Line";
    initialX=initialY=finalX=finalY=-1;
    setButtonsUnchecked();
    this->ui->straightLineButton->setChecked(true);
    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);

    update();
}

void MainWindow::on_freeHandButton_clicked()
{
    paintFlag="Free Hand";
    initialX=initialY=finalX=finalY=-1;
    setButtonsUnchecked();
    this->ui->freeHandButton->setChecked(true);
    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;
    update();
}

void MainWindow::on_squareButton_clicked()
{
    paintFlag="Square";
    setButtonsUnchecked();
    this->ui->squareButton->setChecked(true);
    initialX=initialY=finalX=finalY=-1;
    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;
    update();
}

void MainWindow::on_rectangleButton_clicked()
{
    paintFlag="Rectangle";
    setButtonsUnchecked();
    this->ui->rectangleButton->setChecked(true);
    initialX=initialY=finalX=finalY=-1;
    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;

    update();
}

void MainWindow::on_circleButton_clicked()
{
    paintFlag="Circle";
    setButtonsUnchecked();
    this->ui->circleButton->setChecked(true);
    initialX=initialY=finalX=finalY=-1;
    tmpSelectedComponentList.clear();

    update();
}

void MainWindow::on_ellipseButton_clicked()
{
    paintFlag="Ellipse";
    setButtonsUnchecked();
    this->ui->ellipseButton->setChecked(true);
    initialX=initialY=finalX=finalY=-1;
    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;
    update();
}

void MainWindow::on_clearButton_clicked()
{
    initialX=initialY=finalX=finalY=-1;
    setButtonsUnchecked();
    model->clearDrawing();
    layerList->clear();
    this->ui->layersList->clear();
    selectedLayerIndex=-1;
    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;
    updateLayerList();
    update();
}

void MainWindow::on_eraserButton_clicked()
{
    paintFlag="Text";
    setButtonsUnchecked();
    initialX=initialY=finalX=finalY=-1;
    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;
    update();
}

void MainWindow::on_color1Button_clicked()
{
    int r,g,b;
    QString styleSheet,sr,sg,sb;

    setButtonsUnchecked();
    this->ui->color1Button->setChecked(true);

    color1=QColorDialog::getColor(nullptr,nullptr,"Select a color");
    color1.getRgb(&r,&g,&b);
    sr=QString::number(r);
    sg=QString::number(g);
    sb=QString::number(b);

    styleSheet="background-color: rgb("+sr+","+sg+","+sb+");";
    this->ui->color1Button->setStyleSheet(styleSheet);
    update();
    initialX=initialY=finalY=finalX=-1;

    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;
}

void MainWindow::on_color2Button_clicked()
{
    int r,g,b;
    QString styleSheet,sr,sg,sb;

    setButtonsUnchecked();

    color2=QColorDialog::getColor(Qt::black,nullptr,"Select a color");
    color2.getRgb(&r,&g,&b);
    sr=QString::number(r);
    sg=QString::number(g);
    sb=QString::number(b);

    styleSheet="background-color: rgb("+sr+","+sg+","+sb+");";
    this->ui->color2Button->setStyleSheet(styleSheet);
    update();
    initialX=initialY=finalY=finalX=-1;
    this->ui->color1Button->setChecked(false);

    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;
}

void MainWindow::on_selectButton_clicked()
{
    setButtonsUnchecked();
    this->ui->selectButton->setChecked(true);
    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;
    initialX=initialY=finalX=finalY=-1;
    paintFlag="Select";
    update();
}

void MainWindow::on_layersList_cellDoubleClicked(int row, int column)
{
    doubleClickedLayerIndex=row;
    DrawableComponents *d=model->getComponentByIndex(doubleClickedLayerIndex);
    QString newName=this->ui->layersList->item(doubleClickedLayerIndex,0)->text();
    d->setComponentName(newName);
    model->updateComponent(doubleClickedLayerIndex,d);
    update();
    doubleClickedLayerIndex=-1;
}

void MainWindow::on_layersList_cellClicked(int row, int column)
{
    if(controlKeyPressed)
    {
        DrawableComponents *d=model->getComponentByIndex(row);
        bool found=false;
        for(int i=0;i<tmpSelectedComponentList.size();i++)
        {
            if(tmpSelectedComponentList.at(i)==d)
            {
                tmpSelectedComponentList.removeAt(i);
                found=true;
                break;
            }
        }
        if(!found) tmpSelectedComponentList.append(d);
    }
    else
    {
    paintFlag="Select";

    setButtonsUnchecked();
    initialX=initialY=finalX=finalY=-1;

    tmpSelectedComponentList.clear();
    selectedLayerIndex=row;
    }
    update();
}


void MainWindow::on_layersList_cellActivated(int row, int column)
{

}


void MainWindow::on_layersList_itemSelectionChanged()
{
}

void MainWindow::on_imageButton_clicked()
{
    for(int i=0;i<=20;i++) this->ui->progressBar->setValue(i);
    QString fileName=QFileDialog::getOpenFileName(this,("Open "), "",("(*.*);;All Files (*)"));
    for(int i=0;i<=20;i++) this->ui->progressBar->setValue(i+20);
    if(fileName!="")
    {
    imageComponent=new ImageComponent(fileName);
    model->addComponent(imageComponent);
    updateLayerList();
    for(int i=0;i<=40;i++) this->ui->progressBar->setValue(i+40);
    update();
    for(int i=0;i<=20;i++) this->ui->progressBar->setValue(i+80);
    this->ui->progressBar->setValue(2);
    }
    setButtonsUnchecked();

}


void MainWindow::on_deleteButton_clicked()
{

    if(paintFlag!="Group" && selectedLayerIndex!=-1 && tmpSelectedComponentList.size()==0)
    {
        model->deleteComponent(selectedLayerIndex);
    }

    if(tmpSelectedComponentList.size()>0)
    {
        QList<DrawableComponents *> *tmp=model->getComponentList();
        for(int i=0;i<tmpSelectedComponentList.size();i++)
        {
            for(int j=0;j<tmp->size();j++)
            {
                if(tmp->at(j)==tmpSelectedComponentList.at(i))
                {
                    tmp->removeAt(j);
                }
            }
        }
        tmpSelectedComponentList.clear();
    }

    updateLayerList();
    setButtonsUnchecked();
    this->ui->layersList->selectRow(-1);
    selectedLayerIndex=-1;
    initialX=initialY=finalX=finalY=-1;


    update();
}

void MainWindow::on_undoButton_clicked()
{
    paintFlag="";
    model->undoActivity();
    updateLayerList();
    update();
    setButtonsUnchecked();
}

void MainWindow::on_redoButton_clicked()
{
    paintFlag="";
    model->redoActivity();
    updateLayerList();
    update();
    setButtonsUnchecked();
}

void MainWindow::on_drawingBoardComboBox_activated(int index)
{
    drawingBoardIndex=index;
    update();
}

void MainWindow::on_deleteButton_2_clicked()
{
    this->ui->progressBar->setValue(50);
    Calculator calculator;
    calculator.show();
    this->ui->progressBar->setValue(100);
    calculator.exec();
    this->ui->progressBar->setValue(0);
}


void MainWindow::on_addNewPageButton_clicked()
{
    resetValues();
    this->ui->progressBar->setValue(40);
    model=new TMModel;
    modelList->append(model);
    currentPageIndex=modelList->size()-1;
    populateMainWindow();
    this->ui->progressBar->setValue(60);
    update();
    this->ui->progressBar->setValue(80);
    updateLayerList();
    this->ui->progressBar->setValue(100);
    this->ui->progressBar->setValue(0);

}

void MainWindow::on_previousPageButton_clicked()
{
    this->ui->progressBar->setValue(20);
    if(currentPageIndex>=1)
    {
        resetValues();
        model=modelList->at(currentPageIndex-1);
        currentPageIndex-=1;
        this->ui->progressBar->setValue(40);
        resetValues();
        this->ui->progressBar->setValue(60);
        updateLayerList();
        this->ui->progressBar->setValue(80);
        update();
        this->ui->progressBar->setValue(100);
    }
    this->ui->progressBar->setValue(0);
}

void MainWindow::on_nextPageButton_clicked()
{
    this->ui->progressBar->setValue(20);
    if(currentPageIndex<modelList->size()-1)
    {
        resetValues();
        model=modelList->at(currentPageIndex+1);
        currentPageIndex+=1;
        this->ui->progressBar->setValue(40);
        resetValues();
        this->ui->progressBar->setValue(60);
        updateLayerList();
        this->ui->progressBar->setValue(80);
        update();
        this->ui->progressBar->setValue(100);
    }
    this->ui->progressBar->setValue(0);
}

void MainWindow::on_deletePageButton_clicked()
{
    this->ui->progressBar->setValue(20);
    if(currentPageIndex<modelList->size()-1 && currentPageIndex!=0 && currentPageIndex!=-1)
    {
        resetValues();
        model=modelList->at(currentPageIndex+1);
        modelList->removeAt(currentPageIndex);
        currentPageIndex++;
        this->ui->progressBar->setValue(40);
        resetValues();
        this->ui->progressBar->setValue(60);
        update();
        this->ui->progressBar->setValue(80);
        updateLayerList();
        this->ui->progressBar->setValue(100);
        this->ui->progressBar->setValue(0);
        return;
    }
    if(currentPageIndex==modelList->size()-1 && currentPageIndex!=0 && currentPageIndex!=-1 )
    {
        resetValues();
        model=modelList->at(currentPageIndex-1);
        modelList->removeAt(currentPageIndex);
        currentPageIndex--;
        this->ui->progressBar->setValue(40);
        resetValues();
        this->ui->progressBar->setValue(60);
        update();
        this->ui->progressBar->setValue(80);
        updateLayerList();
        this->ui->progressBar->setValue(100);
        this->ui->progressBar->setValue(0);
        return;
    }
    if(modelList->size()==1)
    {
        resetValues();
        this->ui->progressBar->setValue(40);
        model=new TMModel;
        modelList->insert(0,model);
        currentPageIndex=0;
        populateMainWindow();
        this->ui->progressBar->setValue(60);
        update();
        this->ui->progressBar->setValue(80);
        updateLayerList();
        this->ui->progressBar->setValue(100);
        this->ui->progressBar->setValue(0);
        modelList->removeAt(1);

    }
}


void MainWindow::on_currentPageLineEdit_returnPressed()
{
    QString text=this->ui->currentPageLineEdit->text();
    if(!text.toInt())
    {
        this->ui->currentPageLineEdit->setText(QString::number(currentPageIndex+1));
    }
    else
    {
        this->ui->progressBar->setValue(30);
        int index=text.toUInt();
        if(index<1) index=1;
        if(index>modelList->size()) index=modelList->size();
        this->ui->currentPageLineEdit->setText(QString::number(index));
        currentPageIndex=index-1;
        model=modelList->at(currentPageIndex);
        this->ui->progressBar->setValue(40);
        resetValues();
        this->ui->progressBar->setValue(60);
        update();
        this->ui->progressBar->setValue(80);
        updateLayerList();
        this->ui->progressBar->setValue(100);
        this->ui->progressBar->setValue(0);
    }
}

void MainWindow::on_createGroupButton_clicked()
{
    if(tmpSelectedComponentList.size()>1)
    {
    QList<DrawableComponents *> *tmp=model->getComponentList();
    groupComponent=new GroupComponent;
    for(int i=0;i<tmpSelectedComponentList.size();i++)
    {
        for(int j=0;j<tmp->size();j++)
        {
            if(tmp->at(j)==tmpSelectedComponentList.at(i))
            {
                tmp->removeAt(j);
            }
        }
        groupComponent->addComponent(tmpSelectedComponentList.at(i));
    }
    model->addComponent(groupComponent);
    tmpSelectedComponentList.clear();
    }
    else
    {
        if(model->getComponentByIndex(selectedLayerIndex)->getComponentType()!="Group") return;
        GroupComponent *g=(GroupComponent *)model->getComponentByIndex(selectedLayerIndex);
        QList<DrawableComponents *> *tmp=g->getComponentList();
        model->deleteComponent(selectedLayerIndex);
        for(int i=0;i<tmp->size();i++)
        {
            model->addComponent(tmp->at(i));
        }
    }


    updateLayerList();
    update();
}

void MainWindow::on_graphButton_clicked()
{
    paintFlag="Graph";
    if(this->ui->graphPopUpFrame->isVisible()) this->ui->graphPopUpFrame->setVisible(false);
    else this->ui->graphPopUpFrame->setVisible(true);
    this->ui->graphPointFrame->setVisible(false);

    if(this->ui->layersList->rowCount()>0 && model->getComponentByIndex(0)->getComponentType()=="Graph")
    {
        this->ui->graphLineButton->setEnabled(true);
        this->ui->graphEllipseButton->setEnabled(true);
        this->ui->graphLocatorButton->setEnabled(true);
    }
    else
    {
        this->ui->graphLineButton->setEnabled(false);
        this->ui->graphEllipseButton->setEnabled(false);
        this->ui->graphLocatorButton->setEnabled(false);
    }

}

void MainWindow::on_graphDrawGraphButton_clicked()
{
    paintFlag="Graph";
    initialX=initialY=finalX=finalY=-1;
    setButtonsUnchecked();
    tmpSelectedComponentList.clear();
    this->ui->layersList->selectRow(-1);

    if(this->ui->layersList->rowCount()!=0)
    {
        on_addNewPageButton_clicked();
    }
    int x,y,width,height;
    QString tmpStr;
    bool ok=false;
    x=this->ui->drawingFrame->x();
    y=this->ui->drawingFrame->y();
    width=this->ui->drawingFrame->width();
    height=this->ui->drawingFrame->height();
    QRect tmp(x,y,width,height);
    tmp.setX(this->ui->drawingFrame->x());
    tmp.setY(this->ui->drawingFrame->y());
    graphComponent=new GraphComponent(tmp);

    tmpStr=this->ui->graphScaleXAxis->text();
    tmpStr.toInt(&ok);
    if(ok) graphComponent->setXScale(tmpStr.toInt());

    tmpStr=this->ui->graphScaleYAxis->text();
    tmpStr.toInt(&ok);
    if(ok) graphComponent->setYScale(tmpStr.toInt());

    if(this->ui->graphQuadrantNumber->text()!="") tmpStr=this->ui->graphQuadrantNumber->text();
    tmpStr.toDouble(&ok);
    if(ok) graphComponent->setQuadrantNumber(tmpStr.toDouble());


    model->addComponent(graphComponent);

    this->ui->graphLineButton->setEnabled(true);
    this->ui->graphEllipseButton->setEnabled(true);
    this->ui->graphLocatorButton->setEnabled(true);

    updateLayerList();
    update();
}

void MainWindow::on_graphExitButton_clicked()
{
    this->ui->graphPopUpFrame->setVisible(false);
    graphFlag="";
    paintFlag="";
}

void MainWindow::on_color2NullButton_clicked()
{
    color2=nullptr;
}

void MainWindow::on_exitButton_clicked()
{
     QApplication::quit();
}

void MainWindow::on_graphLocatorButton_clicked()
{
    if(this->ui->layersList->rowCount()>0 && model->getComponentTypeByIndex(0)=="Graph")
    {
    this->ui->graphPopUpFrame->setVisible(false);
    this->ui->graphPointFrame->setVisible(true);
    paintFlag="Graph";
    }
}

void MainWindow::on_graphPointFrameExitButton_clicked()
{
    this->ui->graphPopUpFrame->setVisible(true);
    this->ui->graphPointFrame->setVisible(false);
    paintFlag="Graph";
    graphFlag="";
}

void MainWindow::on_graphPointLocateButton_clicked()
{
    paintFlag="Graph";
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
    bool ok1,ok2;
    double scaledX=this->ui->graphPointAbscissa->text().toDouble(&ok1);
    double scaledY=this->ui->graphPointOrdinate->text().toDouble(&ok2);
    QPointF unscaledPoint;
    if(ok1 && ok2)
    {
        graphComponent=(GraphComponent *)model->getComponentByIndex(0);
        unscaledPoint=graphComponent->getUnscaledPoint(QPointF(scaledX,scaledY));
        pointComponent=new PointComponent;
        QPen pen;
        pen.setWidth(8);
        pen.setColor(this->color1);
        pointComponent->setPen(pen);
        pointComponent->setPoint(unscaledPoint);
        graphComponent->addComponent(pointComponent);
    }
    update();
}

void MainWindow::on_graphPointLocatorButton_clicked()
{
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
paintFlag="Graph";
    qDebug() <<"CONTROLLL AAYAAAA";
    initialX=finalX=initialY=finalY=-1;
    graphFlag="Point";
    graphLocator=true;
    this->ui->graphPointFrame->setVisible(false);
}

void MainWindow::on_graphLineButton_clicked()
{
    if(this->ui->layersList->rowCount()>0 && model->getComponentTypeByIndex(0)=="Graph")
    {
        this->ui->graphPopUpFrame->setVisible(false);
        this->ui->graphLineFrame->setVisible(true);
        paintFlag="Graph";
    }
}

void MainWindow::on_graphLineFrameExitButton_clicked()
{
    this->ui->graphPopUpFrame->setVisible(true);
    this->ui->graphLineFrame->setVisible(false);
    graphFlag="";
    paintFlag="Graph";
}

void MainWindow::on_graphLineLocatorButton_clicked()
{
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
    bool ok1,ok2,ok3,ok4;
    double scaledX1=this->ui->graphLineP1X->text().toDouble(&ok1);
    double scaledY1=this->ui->graphLineP1Y->text().toDouble(&ok2);
    double scaledX2=this->ui->graphLineP2X->text().toDouble(&ok3);
    double scaledY2=this->ui->graphLineP2Y->text().toDouble(&ok4);
    QPointF unscaledPoint1,unscaledPoint2;
    if(ok1 && ok2 && ok3 && ok4)
    {
        graphComponent=(GraphComponent *)model->getComponentByIndex(0);
        unscaledPoint1=graphComponent->getUnscaledPoint(QPointF(scaledX1,scaledY1));
        unscaledPoint2=graphComponent->getUnscaledPoint(QPointF(scaledX2,scaledY2));
        lineComponent=new LineComponent;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(this->color1);
        lineComponent->setLinePen(pen);
        lineComponent->setLine(QLineF(unscaledPoint1,unscaledPoint2));
        graphComponent->addComponent(lineComponent);
    }
    paintFlag="Graph";
    update();
}

void MainWindow::on_graphLineP1Locator_clicked()
{
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
paintFlag="Graph";
    graphFlag="LineP1";
    graphLocator=true;
    this->ui->graphLineFrame->setVisible(false);
}

void MainWindow::on_graphLineP2Locator_clicked()
{
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
paintFlag="Graph";
    graphFlag="LineP2";
    graphLocator=true;
    this->ui->graphLineFrame->setVisible(false);
}

void MainWindow::on_graphLineDrawButton_clicked()
{
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
    initialX=finalX=initialY=finalY=-1;
    paintFlag="Graph";
    graphFlag="Line";
    graphLocator=true;
    this->ui->graphLineFrame->setVisible(false);
}

void MainWindow::on_graphEllipseButton_clicked()
{
    if(this->ui->layersList->rowCount()>0 && model->getComponentTypeByIndex(0)=="Graph")
    {
        this->ui->graphPopUpFrame->setVisible(false);
        this->ui->graphEllipseFrame->setVisible(true);
        paintFlag="Graph";
    }
}

void MainWindow::on_grapgEllipseExitButton_clicked()
{
    this->ui->graphPopUpFrame->setVisible(true);
    this->ui->graphEllipseFrame->setVisible(false);
    paintFlag="Graph";
    graphFlag="";
}

void MainWindow::on_graphEllipseCenterLocateButton_clicked()
{
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
paintFlag="Graph";
    graphFlag="EllipseCenter";
    graphLocator=true;
    this->ui->graphEllipseFrame->setVisible(false);
}

void MainWindow::on_graphEllipseLocateButton_clicked()
{
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
    bool ok1,ok2,ok3,ok4;
    double xScale,yScale;
    double scaledCX=this->ui->graphEllipseCenterAbscissa->text().toDouble(&ok1);
    double scaledCY=this->ui->graphEllipseCenterOrdinate->text().toDouble(&ok2);
    double scaledWidth=this->ui->graphEllipseWidth->text().toDouble(&ok3);
    double scaledHeight=this->ui->graphEllipseHeight->text().toDouble(&ok4);
    QPointF unscaledCenterPoint;
    double unscaledWidth,unscaledHeight,unscaledX1,unscaledY1;
    if(ok1 && ok2)
    {
        if(!ok3) scaledWidth=1;
        if(!ok4) scaledHeight=1;
        graphComponent=(GraphComponent *)model->getComponentByIndex(0);
        xScale=graphComponent->getXScale();
        yScale=graphComponent->getYScale();
        unscaledCenterPoint=graphComponent->getUnscaledPoint(QPointF(scaledCX,scaledCY));

        unscaledWidth=xScale*scaledWidth;
        unscaledHeight=yScale*scaledHeight;
        unscaledX1=unscaledCenterPoint.x()-unscaledWidth;
        unscaledY1=unscaledCenterPoint.y()-unscaledHeight;


        QRect tmpRect;
        tmpRect.setX(unscaledX1);
        tmpRect.setY(unscaledY1);
        tmpRect.setWidth(unscaledWidth*2);
        tmpRect.setHeight(unscaledHeight*2);

        ellipseComponent=new EllipseComponent;
        ellipseComponent->setRectangle(tmpRect);


        QPen pen;
        pen.setWidth(5);
        pen.setColor(this->color1);
        ellipseComponent->setPen(pen);
        graphComponent->addComponent(ellipseComponent);
    }
    paintFlag="Graph";
    update();
}

void MainWindow::on_graphEllipseDrawButton_clicked()
{
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
    initialX=finalX=initialY=finalY=-1;
    graphFlag="Ellipse";
    graphLocator=true;
    this->ui->graphEllipseFrame->setVisible(false);
    paintFlag="Graph";
}

void MainWindow::on_graphUndoButton_clicked()
{
    if(this->ui->layersList->rowCount()==0 && model->getComponentByIndex(0)->getComponentType()!="Graph") return;
    graphComponent=(GraphComponent *)model->getComponentByIndex(0);
    graphComponent->removeLast();
    paintFlag="Graph";
    update();
}
