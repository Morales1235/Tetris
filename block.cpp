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

//template<class T>
//void Block::move(T x, T y);

void Block::move(QPoint & point)
{
    pos += point;
    int i = 0;
    for (unsigned int m = 0; m < g_matrix().size(); m++)
    {
        for (unsigned int n = 0; n < g_matrix()[m].size(); n++)
        {
            if (g_matrix()[m][n])
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

std::array<std::array<bool, 3>, 3> Block::g_matrix()
{
    return matrix;
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

std::array<std::array<bool, 3>, 3> I::g_matrix()
{
    return this->matrix;
}
