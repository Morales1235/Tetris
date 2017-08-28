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
    Block(QWidget *parent);
    ~Block();
    void move(int x, int y);    /// \brief mvoes the tyetromino by the x and y
protected:
    QVector<QSharedPointer<QLabel> > squares; /// \brief squares are parts of each tetromino
};

class I: public Block
{
public:
    I();
};

#endif // BLOCK_H
