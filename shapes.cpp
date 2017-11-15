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
    /*
    switch (number) {
    case LIGHT_BLUE:
        return std::pair <myMatrix, QPixmap> (matrix_I, *lightBluePixmap.get());
        break;
    case DARK_BLUE:
        return std::pair <myMatrix, QPixmap> (matrix_J, *darkBluePixmap.get());
        break;
    case ORANGE:
        return std::pair <myMatrix, QPixmap> (matrix_L, *orangePixmap.get());
        break;
    case YELLOW:
        return std::pair <myMatrix, QPixmap> (matrix_O, *yellowPixmap.get());
        break;
    case GREEN:
        return std::pair <myMatrix, QPixmap> (matrix_S, *greenPixmap.get());
        break;
    case PURPLE:
        return std::pair <myMatrix, QPixmap> (matrix_T, *purplePixmap.get());
        break;
    case RED:
        return std::pair <myMatrix, QPixmap> (matrix_Z, *redPixmap.get());
        break;
    default:
        break;
    }
    */
}

QPixmap Shapes::getPixmap(int number)
{
    return pixmaps[number];
}








