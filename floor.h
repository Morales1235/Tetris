#ifndef FLOOR_H
#define FLOOR_H

#include <array>
#include <unordered_map>
#include <QPixmap>
#include <QLabel>
#include <memory>

//extern std::unordered_map<std::string, QPixmap> colors;
extern QSize blockSize;

class Floor
{
public:
    Floor(QWidget * parent);
    void resetMatrix();
    void addBlockToMatrix(int i, int j);                /// \brief adds a simple one block to the matrix
    void setBlockColor(const QPixmap *pixmap, int i, int j);  /// \brief sets pixmap for block
    std::array<std::array<std::shared_ptr<QLabel>, 10>, 15> getMatrix();   /// \return the matrix of this floor
    bool isRowFull(int i);                      /// \brief checks if row is full of blocks
    void resetMatrixRow(int i);                       /// \brief deletes block in i row

private:
    std::array<std::array<std::shared_ptr<QLabel>, 10>, 15> matrix;   /// \param floorMatrix is matrix representing fallen tetrominos
    QWidget * parent;
};

#endif // FLOOR_H
