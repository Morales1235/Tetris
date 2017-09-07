#include "widget.h"
#include <QApplication>
#include <iostream>
#include <unordered_map>
#include <cstdlib>

QPoint nextBlockPoint = QPoint(450, 100);
QPoint startPoint = QPoint(130, -10);
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

    w.show();

    return a.exec();
}
