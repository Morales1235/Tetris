#include "widget.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;


    I I1(dynamic_cast<QWidget *>(&w), QPoint(130, -10));
    I1.display();
    //w.setCurrentBlock(dynamic_cast<I*>(&w));
    w.setCurrentBlock(&I1);

    w.show();

    return a.exec();
}
