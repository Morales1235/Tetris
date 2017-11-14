#include <QApplication>
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include "widget.h"

QPoint nextPoint = QPoint(420, 100);
QPoint startPoint = QPoint(130, -10);
QSize blockSize = QSize(40, 40);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);

    Widget w;

    w.show();

    return a.exec();
}
