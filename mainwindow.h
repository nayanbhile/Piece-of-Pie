#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPaintEvent>
#include<QDebug>
#include<QBoxLayout>
#include<calculator.h>
#include<QColorDialog>
#include<QPaintDevice>
#include<QPaintEngine>
#include<QMessageBox>
#include<drawablecomponents.h>
#include<linecomponent.h>
#include<rectanglecomponent.h>
#include<squarecomponent.h>
#include<ellipsecomponent.h>
#include<circlecomponent.h>
#include<freehandcomponent.h>
#include<imagecomponent.h>
#include<graphcomponent.h>
#include<pointcomponent.h>
#include<tmmodel.h>
#include<QMouseEvent>
#include<QTableWidget>
#include<QtMultimedia/QAudio>
#include<QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_straightLineButton_clicked();

    void on_freeHandButton_clicked();

    void on_squareButton_clicked();

    void on_rectangleButton_clicked();

    void on_circleButton_clicked();

    void on_ellipseButton_clicked();

    void on_clearButton_clicked();

    void on_eraserButton_clicked();

    void on_color1Button_clicked();

    void on_color2Button_clicked();



    void on_selectButton_clicked();

    void on_layersList_cellDoubleClicked(int row, int column);

    void on_layersList_cellClicked(int row, int column);


    void on_layersList_cellActivated(int row, int column);


    void on_layersList_itemSelectionChanged();

    void on_imageButton_clicked();

    void on_deleteButton_clicked();

    void on_undoButton_clicked();

    void on_redoButton_clicked();

    void on_drawingBoardComboBox_activated(int index);

    void on_deleteButton_2_clicked();

    void on_highlighterButton_clicked();

    void on_clearHighlightsButton_clicked();

    void on_addNewPageButton_clicked();

    void on_previousPageButton_clicked();

    void on_nextPageButton_clicked();

    void on_deletePageButton_clicked();

    void on_currentPageLineEdit_returnPressed();

    void on_createGroupButton_clicked();

    void on_graphButton_clicked();

    void on_graphDrawGraphButton_clicked();

    void on_graphExitButton_clicked();

    void on_color2NullButton_clicked();

    void on_exitButton_clicked();

    void on_graphLocatorButton_clicked();

    void on_graphPointFrameExitButton_clicked();

    void on_graphPointLocateButton_clicked();

    void on_graphPointLocatorButton_clicked();

    void on_graphLineButton_clicked();

    void on_graphLineFrameExitButton_clicked();

    void on_graphLineLocatorButton_clicked();

    void on_graphLineP1Locator_clicked();

    void on_graphLineP2Locator_clicked();

    void on_graphLineDrawButton_clicked();

    void on_graphEllipseButton_clicked();

    void on_grapgEllipseExitButton_clicked();

    void on_graphEllipseCenterLocateButton_clicked();

    void on_graphEllipseLocateButton_clicked();

    void on_graphEllipseDrawButton_clicked();

    void on_graphUndoButton_clicked();

private:
    Ui::MainWindow *ui;
    void populateMainWindow();
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void setIcons();
    void setCursor();
    void resetValues();
    void setFrameBackground(QPainter *painter ,int clipboardIndex);
    bool pointOnDrawingBoard(QPointF point);
    void updateLayerList();
    void setButtonsUnchecked();
    void moveSelectedComponent(DrawableComponents *d,int dx,int dy);
    void moveTheGroup(DrawableComponents *d, int dx, int dy);
    DrawableComponents *getComponentCopy(DrawableComponents *d);

    QList<TMModel *> *modelList;
    int drawingBoardIndex,currentPageIndex;
    int initialX,initialY,finalX,finalY,selectedLayerIndex,rectangleCorner,ellipseCorner;
    int doubleClickedLayerIndex;
    bool triggerReleased,selectTrigger,resizeTrigger,controlKeyPressed;
    bool graphLocator=false;
    QString graphFlag;
    QColor color1,color2;
    QPointF resizingPoint;
    QList<int> xList,yList;
    QList<DrawableComponents *> tmpSelectedComponentList,copiedComponentList;
    QList<QString> activityLog;
    QStringList *layerList;
    LineComponent *lineComponent;
    RectangleComponent *rectangleComponent;
    SquareComponent *squareComponent;
    CircleComponent *circleComponent;
    EllipseComponent *ellipseComponent;
    FreeHandComponent *freeHandComponent;
    GroupComponent *groupComponent;
    GraphComponent *graphComponent;
    ImageComponent *imageComponent;
    PointComponent *pointComponent;
    TMModel *model;

    QString paintFlag;
};
#endif // MAINWINDOW_H
