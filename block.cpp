#include "block.h"

Block::Block()
{
}

Block::Block(QWidget *parent)
{
    for (int i = 0; i < 4; i++) squares.push_back(QSharedPointer<QLabel>(new QLabel));
}

Block::~Block()
{
    squares.clear();
}

void Block::move(int x, int y)
{
    for (auto i: squares) i->move(x, y);
}

I::I()
{

}
