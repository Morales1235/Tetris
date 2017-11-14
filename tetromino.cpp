#include "tetromino.h"


Tetromino::Tetromino()
{
}

Tetromino::Tetromino(QWidget *parent, QPoint &position):
    parent(parent), shapeNumber(shapeNumber)
{
    squaresInit(parent);
    shapeNumber = static_cast<shapes> (rand() % RED + 1);
    switch (shapeNumber) {
    case LIGHT_BLUE:
        matrix = matrix_I;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/light_blue.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case DARK_BLUE:
        matrix = matrix_J;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/dark_blue.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case ORANGE:
        matrix = matrix_L;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/orange.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case YELLOW:
        matrix = matrix_O;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/yellow.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case GREEN:
        matrix = matrix_S;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/green.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case PURPLE:
        matrix = matrix_T;
        for (auto s: squares) s->setPixmap(QPixmap("./graphics/purple.jpg").scaled(blockSize, Qt::KeepAspectRatio));
        break;
    case RED:
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
matrix(other.matrix), pos(other.pos), shapeNumber(other.shapeNumber)
{
    parent = new QWidget;
    parent = other.parent;
    squaresInit(parent);
}

Tetromino::~Tetromino()
{
    squares.clear();
}

void Tetromino::move(int x, int y)
{
    pos += QPoint(int(x), int(y));
    QVector<std::shared_ptr<QLabel> >::iterator it = squares.begin();

    for (unsigned int m = 0; m < getMatrix().size(); m++)
    {
        for (unsigned int n = 0; n < getMatrix()[m].size(); n++)
        {
            if (getMatrix()[m][n])
            {
                it->get()->move(pos + QPoint(n, m) * blockSize.width());
                it++;
            }
        }
    }
}

void Tetromino::setPosition(QPoint & point)
{
    pos = QPoint(0, 0);
    move(point.x(), point.y());
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
    for (int i = 0; i < 4; i++)
    {
        try {squares.push_back(std::shared_ptr<QLabel> (new QLabel(parent)));}
        catch (std::bad_alloc & e) {std::cout << e.what() << " in squaresInit" << std::endl;}
        squares.last()->resize(blockSize);
    }
}


