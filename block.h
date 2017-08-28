/**
  \brief    This is an abstract class representing one tetromino.
  **/

#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QVector>

class Block
{
public:
    Block();
    Block(QWidget *parent);
    ~Block();
    void move(int x, int y);    /// \brief mvoes the tyetromino by the x and y
private:
    QVector<QSharedPointer<QLabel> > squares;
};

#endif // BLOCK_H
