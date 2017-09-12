#include "floor.h"

Floor::Floor()
{
    for (int i = 0; i < matrix.size(); i++)
        matrix[i].fill(0);
}

void Floor::addItemToMatrix(int i, int j)
{
    matrix[i][j] = true;
}

std::array<std::array<bool, 10>, 15> Floor::getMatrix()
{
    return matrix;
}
