#include "widget.h"
#include <QApplication>
#include <iostream>
#include <unordered_map>
#include <cstdlib>

QPoint nextBlockPoint;
QPoint startPoint = QPoint(130, -50);
QSize blockSize = QSize(40, 40);

int loss(int min, int max)
{
    return rand() % max + min;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);


    Widget w;


    //Block * Z = new Block(dynamic_cast<QWidget *>(&w), startPoint, colors["light_blue"], loss(1, 7));
    w.setCurrentBlock(new Block(dynamic_cast<QWidget *>(&w), startPoint, loss(1, 7)));

    Floor my_floor(dynamic_cast<QWidget *>(&w));

    w.show();

    return a.exec();
}
