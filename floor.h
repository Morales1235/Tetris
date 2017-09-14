#ifndef FLOOR_H
#define FLOOR_H

#include <array>
#include <unordered_map>
#include <QPixmap>
#include <QLabel>
#include <memory>

//extern std::unordered_map<std::string, QPixmap> colors;

class Floor
{
public:
    Floor(QWidget * parent);
    void resetMatrix();
    void addItemToMatrix(int i, int j);                /// \brief adds a simple one block to the matrix
    void setBlockColor(QPixmap pixmap, int i, int j);  /// \brief sets pixmap for block
    std::array<std::array<std::shared_ptr<QLabel>, 10>, 15> getMatrix();   /// \return the matrix of this floor

private:
    std::array<std::array<std::shared_ptr<QLabel>, 10>, 15> matrix;   /// \param floorMatrix is matrix representing fallen tetrominos
    QWidget * parent;
};

#endif // FLOOR_H
