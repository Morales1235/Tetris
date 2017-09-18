#include "tetromino.h"


Tetromino::Tetromino()
{
}

Tetromino::Tetromino(QWidget *parent, QPoint &position, int shapeNumber):
    parent(parent), shapeNumber(shapeNumber)
{
    squaresInit(parent);
    switch (shapeNumber) {
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
    for (auto s: squares) s->show();
    setPosition(position);
}

Tetromino::Tetromino(const Tetromino &other):    //!parent are the same for all tetrominos
matrix(other.matrix), pos(other.pos), shapeNumber(other.shapeNumber), blocks(other.blocks)
{
    parent = new QWidget;
    parent = other.parent;
    squaresInit(parent);
}

Tetromino::~Tetromino()
{
    squares.clear();
}

void Tetromino::move(QPoint & point)
{
    move(point.x(), point.y());
}

void Tetromino::setPosition(QPoint &point)
{
    pos = QPoint(0, 0);
    move(point);
}

QPoint Tetromino::getPos()
{
    return pos;
}

myMatrix Tetromino::getMatrix()
{
    return matrix;
}

void Tetromino::transponse()
{
    myMatrix newMatrix;
    for (unsigned int i = 0; i < matrix.size(); i++)
    {
        for (unsigned int j = 0; j < matrix[0].size(); j++)
        {
            newMatrix[i][j] = matrix[j][i];
        }
    }
    matrix = newMatrix;
    move(0, 0);
}

void Tetromino::horizontalReflection()
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

void Tetromino::verticalReflection()
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

int Tetromino::getShapeNumber()
{
    return shapeNumber;
}


void Tetromino::removeSquares()
{
    for (auto s: squares) s->clear();
}

const QPixmap *Tetromino::getPixmap()
{
    return squares.last()->pixmap();
}

Tetromino Tetromino::operator =(const Tetromino & other)
{
    parent = new QWidget;
    parent = other.parent;
    matrix = other.matrix;
    squares.clear();
    squaresInit(parent);
    pos = other.pos;
    shapeNumber = other.shapeNumber;
    blocks = other.blocks;
    return * this;
}

myMatrix Tetromino::operator= (const myMatrix & newMatrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            matrix[i][j] = newMatrix[i][j];
        }
    }
    return matrix;
}

void Tetromino::squaresInit(QWidget *parent)
{
    for (int i = 0; i < blocks; i++)
    {
        try {squares.push_back(std::shared_ptr<QLabel> (new QLabel(parent)));}
        catch (std::bad_alloc & e) {std::cout << e.what() << " in squaresInit" << std::endl;}
        squares[i]->resize(blockSize);
    }
}


