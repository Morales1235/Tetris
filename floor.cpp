#include "floor.h"

Floor::Floor(QWidget * parent):
    parent(parent)
{
    resetMatrix();
}

void Floor::resetMatrix()
{
    for (int i = 0; i < matrix.size(); i++)
        resetMatrixRow(i);
}

void Floor::resetMatrixRow(int i)
{
    matrix[i].fill(nullptr);
}

void Floor::addBlockToMatrix(int i, int j, const QPixmap * pixmap)
{
    matrix[i][j] = std::shared_ptr <QLabel> (new QLabel(parent));
    matrix[i][j]->move(QPoint(10 + blockSize.width() * j, -10 + blockSize.height() * i));
    matrix[i][j]->setPixmap(*pixmap);
    matrix[i][j]->show();
}

std::array<std::array<std::shared_ptr<QLabel>, 10>, 15> Floor::getMatrix()
{
    return matrix;
}

bool Floor::isRowFull(int i)
{
    return std::all_of(matrix[i].cbegin(), matrix[i].cend(), [] (std::shared_ptr <QLabel> j){return j != nullptr;});
}

void Floor::moveDownBlocks(int endRow)
{
    moveDownPixmaps(endRow);
    moveDownMatrix(endRow);
}

void Floor::moveDownPixmaps(int endRow)
{
    for (int i = endRow - 1; i > 0; i--)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j])
                matrix[i][j]->move(j * blockSize.width() + 10, (i + 1) * blockSize.height() - 10);
        }
    }
}

void Floor::moveDownMatrix(int endRow)
{
    for (int i = endRow; i > 0; i--)
    {
            for (int j = 0; j < matrix[i].size(); j++)
                matrix[i][j] = matrix[i - 1][j];

    }
}


