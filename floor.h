#ifndef FLOOR_H
#define FLOOR_H

#include<array>

class Floor
{
public:
    Floor();
    void addItemToMatrix(int i, int j);                /// \brief adds a simple one block to the matrix
    std::array<std::array<bool, 10>, 15> getMatrix();   /// \return the matrix of this floor

private:
    std::array<std::array<bool, 10>, 15> matrix;   /// \param floorMatrix is matrix representing fallen tetrominos
};

#endif // FLOOR_H
