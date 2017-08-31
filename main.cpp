#include "widget.h"
#include <QApplication>
#include <iostream>
#include <unordered_map>
#include <cstdlib>

QPoint nextBlockPoint;
QPoint startPoint = QPoint(130, -50);
std::unordered_map<std::string, QPixmap> colors;
QSize blockSize = QSize(40, 40);

int loss(int min, int max)
{
    return rand() % max + min;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);

    //Pixmap - colors definition
    colors.insert({"light_blue", QPixmap("./graphics/light_blue.jpg").scaled(blockSize, Qt::KeepAspectRatio)});

    //std::cout << typeid(colors[""])

    Widget w;

    //Block * Z = new Block(dynamic_cast<QWidget *>(&w), startPoint, colors["light_blue"], loss(1, 7));
    w.setCurrentBlock(new Block(dynamic_cast<QWidget *>(&w), startPoint, colors["light_blue"], loss(1, 7)));

    w.show();

    return a.exec();
}
