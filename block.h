/**
  \brief    This is an abstract(not yet?) class representing one tetromino.
  **/

#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QVector>
#include <iostream>
#include <typeinfo>

extern QSize blockSize;

typedef std::array<std::array<bool, 5>, 5> myMatrix;

class Block
{
public:
    Block();
    Block(QWidget * parent, QPoint & position, QPixmap color, int shape);
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
        for (unsigned int m = 0; m < g_matrix().size(); m++)
        {
            for (unsigned int n = 0; n < g_matrix()[m].size(); n++)
            {
                if (g_matrix()[m][n])
                {
                    squares[i]->move(pos + QPoint(n, m) * blockSize.width());
                    if (n < left) left = n;
                    else if (right < n) right = n;
                    std::cout <<" pos: " << left << ", " << right << std::endl;
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
    void change_matrix(myMatrix newMatrix);  /// \brief change the matrix representing tetromino
    myMatrix g_matrix(); /// \brief returns matrix representing tetromino
    void transponse();      /// \brief transposing the matrix of tetromino
    void horizontalReflection();        /// \brief Reflects the matrix by horizontal axis
    void verticalReflection();        /// \brief Reflects the matrix by vertical axis
    int g_shape();                  /// \return the number of the shape(matrix)
    bool leftBorder();              /// \brief checks if tetromino touched left border of playground
    bool rightBorder();              /// \brief checks if tetromino touched right border of playground
    //members
protected:
    //methods
    void squaresInit(QWidget * parent); /// \brief adds squares to QVector and sets it size
    //members
    myMatrix matrix = {{{{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}}}; /// \param matrix represents the shape of tetromino
    QVector<QLabel*> squares;       /// \param squares represents every square in tetromino
    QPoint pos;                         /// \param pos position of left top corner of matrix representing tetromino
    int left = 0;              /// \param width is the width of tetromino
    int right = 0;             /// \param height is the height of tetromino
    int shape;              /// \param fro choosing which matrix represents shape

    //!Matrixes used to represent each tetromino
    //! Which matrix must be the same, because of definition of objects... blah
    //! They are 5x5 to fit all matrixes - biggest (I) has 4
    //! But it also gives 3x3 tetrominos posibility to rotate around its middle square
    myMatrix matrix_I = {{{{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{1, 1, 1, 1, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_J = {{{{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 1, 1, 1, 0}},
                          {{0, 0, 0, 1, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_L = {{{{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 1, 1, 1, 0}},
                          {{0, 1, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_O = {{{{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 1, 1, 0, 0}},
                          {{0, 1, 1, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_S = {{{{0, 0, 0, 0, 0}},
                          {{0, 0, 1, 1, 0}},
                          {{0, 1, 1, 0, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_T = {{{{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 1, 1, 1, 0}},
                          {{0, 0, 1, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};

    myMatrix matrix_Z = {{{{0, 0, 0, 0, 0}},
                          {{0, 1, 1, 0, 0}},
                          {{0, 0, 1, 1, 0}},
                          {{0, 0, 0, 0, 0}},
                          {{0, 0, 0, 0, 0}}}};
};
/*
class I: public Block
{
public:
    I(QWidget * parent, QPoint & position);
    //methods
    void display(); /// \brief adds graphics to tetromino
    //variables
    myMatrix matrix = {{{{0, 0, 0, 0}}, {{1, 1, 1, 1}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}};  /// \param matrix represents the shape of tetromino
protected:
    myMatrix g_matrix();          /// \return matrix representing tetromino
};

class Z: public Block
{
public:
    Z(QWidget * parent, QPoint & position);
    //methods
    void display(); /// \brief adds graphics to tetromino
    //variables
    myMatrix matrix = {{{{0, 0, 0, 0}}, {{1, 1, 0, 0}}, {{0, 1, 1, 0}}, {{0, 0, 0, 0}}}};  /// \param matrix represents the shape of tetromino
protected:
    myMatrix g_matrix();          /// \brief returns matrix representing tetromino
    friend void change_matrix(Block block, myMatrix newMatrix);
};

void change_matrix(Block block, myMatrix newMatrix);
*/
#endif // BLOCK_H
