/**
  \brief    This is an abstract(not yet?) class representing one tetromino.
  **/

#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QVector>

class Block
{
public:
    Block();
    Block(const Block &other);
    ~Block();
    void move(int & x, int & y);    /// \brief mvoes the tyetromino by the x and y
    void move(int x, int y);        /// \brief mvoes the tetromino by the x and y
    void move(QPoint & point);    /// \brief mvoes the tetromino by the QPoint
    void setPos(QPoint & leftTop);
protected:
    QVector<QLabel*> squares;
    void squaresInit(QWidget * parent);
    QPoint pos;
    int matrixI[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
private:
};

class I: public Block
{
public:
    I(QWidget * parent, QPoint & position);
    I(QWidget * parent, QPoint position);
    //methods
    void display();
    //variables
};

#endif // BLOCK_H
