#include "block.h"

Block::Block()
{
}

Block::~Block()
{
    squares.clear();
}

void Block::move(int & x, int & y)
{
    m_x += x;
    m_y += y;
    for (auto i: squares) i->move(x, y);
}

void Block::move(QPoint & point)
{
    for (auto s: squares) s->move(point);
}

void Block::squaresInit(QWidget *parent)
{
    for (int i = 0; i < 4; i++)
    {
        squares.push_back(new QLabel(parent));
        squares.last()->resize(QSize(40, 40));
    }
}

I::I(QWidget * parent, QPoint & position)
{
    squaresInit(parent);
    move(position);
}

I::I(QWidget * parent, QPoint position)
{
    squaresInit(parent);
    move(position);
}


void I::display()
{
    for (auto s: squares) s->setPixmap(QPixmap("./graphics/light_blue.jpg").scaled(s->size(), Qt::KeepAspectRatio));
}
