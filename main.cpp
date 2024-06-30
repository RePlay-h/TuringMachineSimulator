#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSize screenSize = a.primaryScreen()->size();
    MainWindow w(screenSize.width(), screenSize.height());

    // calculate screen center
    int centerX = (screenSize.width()-w.size().width())/2;
    int centerY = (screenSize.height()-w.size().height())/2;

    w.setWindowTitle("TuringMachine"); // set title
    w.move(centerX, centerY); // set pos of MainWindow

    w.show();
    return a.exec();
}
