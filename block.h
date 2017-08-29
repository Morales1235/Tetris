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
    ~Block();
    void move(int & x, int & y);    /// \brief mvoes the tyetromino by the x and y
    void move(QPoint & point);    /// \brief mvoes the tetromino by the QPoint
protected:
    QVector<QLabel*> squares;
    void squaresInit(QWidget * parent);
private:
    int m_x;        /// \param m_x x coordinate of block
    int m_y;        /// \param m_y y coordinate of block
};

class I: public Block
{
public:
    I(QWidget * parent, QPoint & position);
    I(QWidget * parent, QPoint position);
    void display();
};

#endif // BLOCK_H
