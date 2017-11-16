#include "shapes.h"

Shapes * Shapes::instance = nullptr;

Shapes::Shapes()
{
    matrixes.push_back(matrix_I);
    matrixes.push_back(matrix_J);
    matrixes.push_back(matrix_L);
    matrixes.push_back(matrix_O);
    matrixes.push_back(matrix_S);
    matrixes.push_back(matrix_T);
    matrixes.push_back(matrix_Z);

    pixmaps.push_back(QPixmap("./graphics/light_blue.jpg").scaled(blockSize, Qt::KeepAspectRatio));
    pixmaps.push_back(QPixmap("./graphics/dark_blue.jpg").scaled(blockSize, Qt::KeepAspectRatio));
    pixmaps.push_back(QPixmap("./graphics/orange.jpg").scaled(blockSize, Qt::KeepAspectRatio));
    pixmaps.push_back(QPixmap("./graphics/yellow.jpg").scaled(blockSize, Qt::KeepAspectRatio));
    pixmaps.push_back(QPixmap("./graphics/green.jpg").scaled(blockSize, Qt::KeepAspectRatio));
    pixmaps.push_back(QPixmap("./graphics/purple.jpg").scaled(blockSize, Qt::KeepAspectRatio));
    pixmaps.push_back(QPixmap("./graphics/red.jpg").scaled(blockSize, Qt::KeepAspectRatio));
}

Shapes *Shapes::getInstance()
{
    if (!instance)
        instance = new Shapes();
    return instance;
}

myMatrix Shapes::getMatrix(int number)
{
    return matrixes[number];
}

QPixmap Shapes::getPixmap(int number)
{
    return pixmaps[number];
}








