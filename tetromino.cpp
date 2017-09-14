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
matrix(other.matrix), pos(other.pos), left(other.left), right(other.right), shapeNumber(other.shapeNumber), top(other.top), bottom(other.bottom), blocks(other.blocks)
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

void Tetromino::squaresInit(QWidget *parent)
{
    for (int i = 0; i < blocks; i++)
    {
        try {squares.push_back(std::shared_ptr<QLabel> (new QLabel(parent)));}
        catch (std::bad_alloc & e) {std::cout << e.what() << " in squaresInit" << std::endl;}
        squares[i]->resize(blockSize);
    }
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
    //delete parent;
    parent = new QWidget;
    parent = other.parent;
    matrix = other.matrix;
    squares.clear();
    squaresInit(parent);
    pos = other.pos;
    left = other.left;
    right = other.right;
    shapeNumber = other.shapeNumber;
    top = other.top;
    bottom = other.bottom;
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
}


/*
//////////////////////////////////////////////////////////////////////////

Floor::Floor(QWidget * parent, QGridLayout * layout):
    parentWidget(parent), floorLayout(layout)
{
    for (int i = 0; i < matrix.size(); i ++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
            matrix[i].fill(0);
    }
    leftCorner = new QPoint(10, 30);
    setPosition(*leftCorner);
    //squaresInit(parentWidget);
    //std::cout << getMatrix();
}

void Floor::addBlock(Block *block)
{
    int m = block->getMatrix().size();
    int n = block->getMatrix()[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (block->getMatrix()[i][j])
            {
                squares.push_back(new QLabel(this->parentWidget));
                squares.last()->resize(blockSize);
                squares.last()->setPixmap(QPixmap("./graphics/dark_blue.jpg").scaled(blockSize, Qt::KeepAspectRatio));
                matrix[(block->getPos().y()/40) + i][(block->getPos().x()/40) + j] = 1;
                floorLayout->removeWidget(dynamic_cast<QWidget *>(floorLayout->itemAtPosition(block->getPos().y()/40 + i, block->getPos().x()/40 + j)));
                floorLayout->addWidget(squares.last(), block->getPos().y()/40 + i, block->getPos().x()/40 + j);
                blocks++;
            }
        }
    }
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            std::cout << getMatrix()[i][j] << " ";
            if (!getMatrix()[i][j])
            {
                floorLayout->addWidget(squares.first() , block->getPos().y()/40 + i, block->getPos().x()/40 + j);
            }
        }
        std::cout << std::endl;
    }
    squaresInit(parentWidget);
    move(0, 0);
}

floorMatrix Floor::getMatrix()
{
    return matrix;
}
*/

