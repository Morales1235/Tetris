/**
 * \details Here are functions operated on matrxes (2D arrays)
 * Used in project to rotate tetrominos (its matrix)
 * **/

#include <array>
#include <iostream>
#include <typeinfo>

typedef std::array<std::array<bool, 4>, 4> myMatrix;

myMatrix transponse(myMatrix mat)
{
    int m = mat.size();
    int n = mat[0].size();
    myMatrix newMatrix;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            newMatrix[i][j] = mat[j][i];
        }
    }
    return newMatrix;
}

myMatrix horizontalReflection(myMatrix mat)
{
    int m = mat.size();
    int n = mat[0].size();
    bool temp = 0;
    for (int i = 0; i < m/2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp = mat[i][j];
            mat[i][j] = mat[m - (1 + i)][j];
            mat[m - (1 + i)][j] = temp;
        }
    }
    return mat;
}
