#include "floor.h"

Floor::Floor(QWidget * parent):
    parent(parent)
{
    resetMatrix();
}

void Floor::resetMatrix()
{
    for (int i = 0; i < matrix.size(); i++)
        matrix[i].fill(nullptr);
}

void Floor::addItemToMatrix(int i, int j)
{
    matrix[i][j] = std::move(std::shared_ptr<QLabel> (new QLabel(parent)));
    matrix[i][j]->move(QPoint(10 + blockSize.width() * j, 30 + blockSize.height() * i));
}

void Floor::setBlockColor(const QPixmap * pixmap, int i, int j)
{
    matrix[i][j]->setPixmap(*pixmap);
    matrix[i][j]->show();
}

std::array<std::array<std::shared_ptr<QLabel>, 10>, 15> Floor::getMatrix()
{
    return matrix;
}


