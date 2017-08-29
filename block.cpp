#include "block.h"

Block::Block()
{
}

Block::Block(const Block &other)
{

}

Block::~Block()
{
    squares.clear();
}

void Block::move(int & x, int & y)
{
    pos += QPoint(x, y);
    for (auto i: squares) i->move(pos);
}

void Block::move(int x, int y)
{
    pos += QPoint(x, y);
    int i = 0;
    for (int m = 0; m < 4; m++)
    {
        for (int n = 0; n < 4; n++)
        {
            if (matrixI[m][n])
            {
                squares[i]->move(pos + QPoint(n, m) * 40);
                i++;
            }
        }
    }
}

void Block::move(QPoint & point)
{
    pos += point;
    int i = 0;
    for (int m = 0; m < 4; m++)
    {
        for (int n = 0; n < 4; n++)
        {
            if (matrixI[m][n])
            {
                squares[i]->move(pos + QPoint(n, m) * 40);
                i++;
            }
        }
    }
}


void Block::squaresInit(QWidget *parent)
{
    for (int i = 0; i < 4; i++)
    {
        squares.push_back(new QLabel(parent));
        squares[i]->resize(QSize(40, 40));
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
