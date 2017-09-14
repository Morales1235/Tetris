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
    matrix[i][j] = std::move(std::unique_ptr<QLabel> (new QLabel(parent)));
}

void Floor::setBlockColor(QPixmap pixmap, int i, int j)
{

}

std::array<std::array<std::shared_ptr<QLabel>, 10>, 15> Floor::getMatrix()
{
    return matrix;
}


