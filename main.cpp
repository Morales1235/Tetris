#include "widget.h"
#include <QApplication>
#include <iostream>

QPoint next;
QPoint startPoint = QPoint(130, 30);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;


    Z * z1 = new Z(dynamic_cast<QWidget *>(&w), startPoint);
    z1->display();
    //w.setCurrentBlock(dynamic_cast<I*>(&w));
    w.setCurrentBlock(z1);

    w.show();

    return a.exec();
}
