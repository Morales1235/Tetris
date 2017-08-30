/**
  \brief    This is an abstract(not yet?) class representing one tetromino.
  **/

#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QVector>
#include <iostream>

class Block
{
public:
    Block();
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
    //members
protected:
    //methods
    void squaresInit(QWidget * parent); /// \brief adds squares to QVector and sets it size
    virtual std::array<std::array<bool, 4>, 4> g_matrix(); /// \brief returns matrix representing tetromino
    //members
    QVector<QLabel*> squares;       /// \param squares represents every square in tetromino
    QPoint pos;                         /// \param pos position of left top corner of matrix representing tetromino
    std::array<std::array<bool, 4>, 4> matrix = {{{{0, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}}; /// \param matrix represents the shape of tetromino
    int width;              /// \param width is the width of tetromino
    int height;             /// \param height is the height of tetromino
};

class I: public Block
{
public:
    I(QWidget * parent, QPoint & position);
    //methods
    void display(); /// \brief adds graphics to tetromino
    //variables
    std::array<std::array<bool, 4>, 4> matrix = {{{{0, 0, 0, 0}}, {{1, 1, 1, 1}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}}};  /// \param matrix represents the shape of tetromino
protected:
    std::array<std::array<bool, 4>, 4> g_matrix();          /// \brief returns matrix representing tetromino
};

class Z: public Block
{
public:
    Z(QWidget * parent, QPoint & position);
    //methods
    void display(); /// \brief adds graphics to tetromino
    //variables
    std::array<std::array<bool, 4>, 4> matrix = {{{{0, 0, 0, 0}}, {{1, 1, 0, 0}}, {{0, 1, 1, 0}}, {{0, 0, 0, 0}}}};  /// \param matrix represents the shape of tetromino
protected:
    std::array<std::array<bool, 4>, 4> g_matrix();          /// \brief returns matrix representing tetromino
};


#endif // BLOCK_H
