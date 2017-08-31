#include "block.h"

Block::Block()
{
}

Block::Block(QWidget *parent, QPoint &position, QPixmap color, int shape):
shape(shape)
{
    switch (shape) {
    case 1:
        matrix = matrix_I;
        break;
    case 2:
        matrix = matrix_J;
        break;
    case 3:
        matrix = matrix_L;
        break;
    case 4:
        matrix = matrix_O;
        break;
    case 5:
        matrix = matrix_S;
        break;
    case 6:
        matrix = matrix_T;
        break;
    case 7:
        matrix = matrix_Z;
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
    left = 3;
    right = 0;
    top = 3;
    bottom = 0;
    for (unsigned int m = 0; m < g_matrix().size(); m++)
    {
        for (unsigned int n = 0; n < g_matrix()[m].size(); n++)
        {
            if (g_matrix()[m][n])
            {
                squares[i]->move(pos + QPoint(n, m) * blockSize.width());
                if (n < left) left = n;
                else if (n > right) right = n;
                if (m < top) top = m;
                else if (bottom < m) bottom = m;
                std::cout <<" pos: " << left << ", " << right << std::endl;
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
        squares[i]->resize(blockSize);
    }
}

myMatrix Block::g_matrix()
{
    return matrix;
}

void Block::transponse()
{
    myMatrix newMatrix;
    for (unsigned int i = 0; i < matrix.size(); i++)
    {
        for (unsigned int j = 0; j < matrix[0].size(); j++)
        {
            newMatrix[i][j] = matrix[j][i];
        }
    }
    //change_matrix(newMatrix);
    matrix = newMatrix;
    move(0, 0);
}

void Block::horizontalReflection()
{
    bool temp = 0;
    int m = matrix.size();
    int n = matrix[0].size();
    for (int i = 0; i < m/2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp = matrix[i][j];
            matrix[i][j] = matrix[m - (1 + i)][j];
            matrix[m - (1 + i)][j] = temp;
        }
    }
    move(0, 0);
}

void Block::verticalReflection()
{
    bool temp = 0;
    int m = matrix.size();
    int n = matrix[0].size();
    for (int i = 0; i < n/2; i++)
    {
        for (int j = 0; j < m; j++)
        {
            temp = matrix[j][i];
            matrix[j][i] = matrix[j][n - (1 + i)];
            matrix[j][n - (1 + i)] = temp;
        }
    }
    move(0, 0);
}

int Block::g_shape()
{
    return shape;
}

bool Block::leftBorder()
{
    return (pos.x() + (left * blockSize.width()) == 10);
}

bool Block::rightBorder()
{
    return (pos.x() + ((right + 1) * blockSize.width()) == 410);
}

bool Block::isAway()
{
    return ((pos.x() + (left * blockSize.width()) < 10) || (pos.x() + ((right + 1) * blockSize.width()) > 410));
}

myMatrix Block::operator= (const myMatrix & newMatrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = newMatrix[i][j];
        }
    }
}


