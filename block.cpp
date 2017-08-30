#include "block.h"

Block::Block()
{
}

Block::Block(QWidget *parent, QPoint &position, QPixmap color, int shape)
{
    switch (shape) {
    case 1:
        change_matrix(matrix_Z);
        break;
    default:
        break;
    }
    squaresInit(parent);
    setPosition(position);
    for (auto s: squares) s->setPixmap(color);
}

Block::Block(const Block &other)
{

}

Block::~Block()
{
    squares.clear();
}

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

void Block::setPosition(QPoint &point)
{
    pos = QPoint(0, 0);
    move(point);
}

QPoint Block::g_pos()
{
    return pos;
}

void Block::squaresInit(QWidget *parent)
{
    for (int i = 0; i < 4; i++)
    {
        squares.push_back(new QLabel(parent));
        squares[i]->resize(QSize(40, 40));
    }
}

myMatrix Block::g_matrix()
{
    return matrix;
}

void Block::transponse()
{
    int m = matrix.size();
    int n = matrix[0].size();
    myMatrix newMatrix;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            newMatrix[i][j] = matrix[j][i];
        }
    }
    change_matrix(newMatrix);
}

void Block::horizontalReflection()     /// \brief reflection of the matrix by horizontal axes
{
    int m = matrix.size();
    int n = matrix[0].size();
    bool temp = 0;
    for (int i = 0; i < m/2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp = matrix[i][j];
            matrix[i][j] = matrix[m - (1 + i)][j];
            matrix[m - (1 + i)][j] = temp;
        }
    }
}

void Block::change_matrix(myMatrix newMatrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = newMatrix[i][j];
        }
    }
}
/*
I::I(QWidget *parent, QPoint &position)
{
    squaresInit(parent);
    setPosition(position);
}

void I::display()
{
    for (auto s: squares) s->setPixmap(QPixmap("./graphics/light_blue.jpg").scaled(s->size(), Qt::KeepAspectRatio));
}

myMatrix I::g_matrix()
{
    return this->matrix;
}

Z::Z(QWidget * parent, QPoint & position)
{
    squaresInit(parent);
    setPosition(position);
}

void Z::display()
{
    for (auto s: squares) s->setPixmap(QPixmap("./graphics/red.jpg").scaled(s->size(), Qt::KeepAspectRatio));
}

myMatrix Z::g_matrix()
{
    return this->matrix;
}

void change_matrix(Block block, myMatrix newMatrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            block.matrix[i][j] = newMatrix[i][j];
        }
    }
}*/
