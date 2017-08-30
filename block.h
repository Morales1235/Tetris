/**
  \brief    This is an abstract(not yet?) class representing one tetromino.
  **/

#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QVector>
#include <iostream>
#include <typeinfo>


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
        for (unsigned int m = 0; m < g_matrix().size(); m++)
        {
            for (unsigned int n = 0; n < g_matrix()[m].size(); n++)
            {
                if (g_matrix()[m][n])
                {
                    squares[i]->move(pos + QPoint(n, m) * 40);
                    width = n + 1;
                    height = m + 1;
                    std::cout << "Width: " << width << ". Height: " << height << std::endl;
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
    //members
protected:
    //methods
    void squaresInit(QWidget * parent); /// \brief adds squares to QVector and sets it size
    //members
    myMatrix matrix = {{{{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}}}; /// \param matrix represents the shape of tetromino
    QVector<QLabel*> squares;       /// \param squares represents every square in tetromino
    QPoint pos;                         /// \param pos position of left top corner of matrix representing tetromino
    int width;              /// \param width is the width of tetromino
    int height;             /// \param height is the height of tetromino

    //!Matrixes used to represent each tetromino
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
