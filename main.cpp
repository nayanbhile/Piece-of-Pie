#include "mainwindow.h"

#include <QApplication>
#include<QLayout>
#include<QSplashScreen>
#include<QTimer>
#include<QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDesktopWidget* desktopWidget = qApp->desktop();
    QPixmap map("SplashScreen\\POPSplashScreen.png");
    QRect screenGeometry = desktopWidget->screenGeometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    QPixmap pixmapForSplash = map.scaled(screenWidth, screenHeight);
    QSplashScreen splashScreen(pixmapForSplash, Qt::WindowStaysOnTopHint);
    splashScreen.show();
    MainWindow w;
    w.showFullScreen();
    QTimer::singleShot(1000,&splashScreen,SLOT(close()));
    w.show();
    return a.exec();
}
