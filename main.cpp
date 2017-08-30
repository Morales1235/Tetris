#include "widget.h"
#include <QApplication>
#include <iostream>
#include <unordered_map>

QPoint nextBlockPoint;
QPoint startPoint = QPoint(130, -50);
std::unordered_map<std::string, QPixmap> colors;
QSize blockSize = QSize(40, 40);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Pixmap - colors definition
    colors.insert({"light_blue", QPixmap("./graphics/light_blue.jpg").scaled(blockSize, Qt::KeepAspectRatio)});

    //std::cout << typeid(colors[""])

    Widget w;

    Block * Z = new Block(dynamic_cast<QWidget *>(&w), startPoint, colors["light_blue"], 1);
    w.setCurrentBlock(Z);

    w.show();

    return a.exec();
}
