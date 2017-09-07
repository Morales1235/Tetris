/**
  \brief    This is an abstract(not yet?) class representing one tetromino.
  **/

#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QVector>
#include <iostream>
#include <typeinfo>
#include <QGridLayout>
#include <memory>

extern QSize blockSize;
extern int loss(int min, int max);

typedef std::array<std::array<bool, 5>, 5> myMatrix;        //!Matrixes used to represent each tetromino
                                                            //!Which matrix must be the same, because of definition of objects... blah
                                                            //!They are 5x5 to fit all matrixes - biggest (I) has 4
                                                            //!But it also gives 3x3 tetrominos posibility to rotate around its middle square

class Block
{
public:
    Block();
    Block(QWidget * parent, QPoint & position);
    Block(const Block &other);
    ~Block();

    //methods
    template<class T>
    void move(T x, T y)     /// \brief mvoes the tetromino by the x and y
    {
        pos += QPoint(int(x), int(y));
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
                    else if (right < n) right = n;
                    if (m < top) top = m;
                    else if (bottom < m) bottom = m;
                    i++;
                }
            }
        }
    }
    void move(QPoint & point);    /// \brief mvoes the tetromino by the QPoint
    template<class T>
    void setPosition(T x, T y)      /// \brief sets position of tetromino
    {
        pos = QPoint(0, 0);
        move(x, y);
    }
    void setPosition(QPoint & point);   /// \brief moves the tetromino to the point
    QPoint g_pos();                     /// \return the position of tetromino
    myMatrix g_matrix(); /// \brief returns matrix representing tetromino
    void transponse();      /// \brief transposing the matrix of tetromino
    void horizontalReflection();        /// \brief Reflects the matrix by horizontal axis
    void verticalReflection();        /// \brief Reflects the matrix by vertical axis
    int g_shape();                  /// \return the number of the shape(matrix)
    bool leftBorder();              /// \brief checks if tetromino touched left border of playground
    bool rightBorder();              /// \brief checks if tetromino touched right border of playground
    bool isAway();                  /// \brief checks if tetromino not only touch, but is away of playground (sides)
    void removeSquares();

    Block operator =(const Block &other);            /// \brief assigment operator for block
    myMatrix operator = (const myMatrix & );    /// \brief change the matrix representing tetromino

    //members
    QVector<std::shared_ptr<QLabel> > squares;       /// \param squares represents every square in tetromino

protected:
    //methods
    void squaresInit(QWidget * parent); /// \brief adds squares to QVector and sets it size

    //members
    QWidget * parent;
    myMatrix matrix = {{{{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}}}; /// \param matrix represents the shape of tetromino
    QPoint pos;                         /// \param pos position of left top corner of matrix representing tetromino
    int left = 3;              /// \param left is left block in matrix of tetromino
    int right = 0;             /// \param height is right block in matrix of tetromino
    int shape;              /// \param shape choosing which matrix represents shape
    int top = 3;                    /// \param top is top block in matrix of tetromino
    int bottom = 0;                 /// \param bottom is bottom block in matrix of tetromino
    int blocks = 4;                 /// \param blocks is number of blocks in tetromino


    myMatrix matrix_I = {{{{0, 0, 0, 0, 0}},
                          {{1, 1, 1, 1, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_J = {{{{0, 0, 0, 0, 0}},
                          {{0, 1, 0, 0, 0}},
                          {{0, 1, 1, 1, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_L = {{{{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 1, 0}},
                          {{0, 1, 1, 1, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_O = {{{{0, 0, 0, 0, 0}},
                          {{0, 1, 1, 0, 0}},
                          {{0, 1, 1, 0, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_S = {{{{0, 0, 0, 0, 0}},
                          {{0, 0, 1, 1, 0}},
                          {{0, 1, 1, 0, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_T = {{{{0, 0, 0, 0, 0}},
                          {{0, 0, 1, 0, 0}},
                          {{0, 1, 1, 1, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_Z = {{{{0, 0, 0, 0, 0}},
                          {{0, 1, 1, 0, 0}},
                          {{0, 0, 1, 1, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};
};

/*
class Floor: public Block   /** \details Class Floor represents fallen block
                              * fallen block should add to floor, which is a big block of tetrominos
                              *
                              **
{
public:
    Floor(QWidget * parent, QGridLayout * layout);
    void addBlock(Block * block);
    floorMatrix g_matrix();
private:
    floorMatrix matrix;
    QPoint * leftCorner;        /// \param leftCorner is point of left corner of matrix - playground
    int blocks = 0;
    QWidget * parentWidget;
    QGridLayout * floorLayout;
};
*/

#endif // BLOCK_H
