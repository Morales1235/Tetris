#include "block.h"

Block::Block()
{
}

Block::Block(QWidget *parent, QPoint &position, int shape):
shape(shape)
{
    squaresInit(parent);
    switch (shape) {
    case 1:
        matrix = matrix_I;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/light_blue.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case 2:
        matrix = matrix_J;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/dark_blue.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case 3:
        matrix = matrix_L;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/orange.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case 4:
        matrix = matrix_O;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/yellow.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case 5:
        matrix = matrix_S;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/green.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case 6:
        matrix = matrix_T;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/purple.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case 7:
        matrix = matrix_Z;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/red.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    default:
        break;
    }
    setPosition(position);
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
                i++;
                std::cout << i << " ";
            }
        }
        std:: cout << std::endl;
    }
    std::cout <<" pos: " << (pos.x() + 10) << ", " << (pos.y() + 10 + bottom * 40) << std::endl;
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
    for (int i = 0; i < blocks; i++)
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
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            matrix[i][j] = newMatrix[i][j];
        }
    }
}

Floor::Floor(QWidget * parent):
    parentWidget(parent)
{
    for (auto m: matrix) m.fill(0);
    leftCorner = new QPoint(10, 30);
    setPosition(*leftCorner);
    squaresInit(parentWidget);
    //std::cout << g_matrix();
}

void Floor::addBlock(Block block)
{
    int m = block.g_matrix().size();
    int n = block.g_matrix()[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (block.g_matrix()[i][j])
                matrix[(block.g_pos().x()/40) + i][(block.g_pos().y()/40) + j] = 1;
        }
    }
    squaresInit(parentWidget);
    move(0, 0);
}

