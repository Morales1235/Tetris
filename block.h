/**
  \brief    This is an abstract(not yet?) class representing one tetromino.
  **/

#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QVector>

class Block
{
public:
    Block();
    Block(const Block &other);
    ~Block();
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
                    i++;
                }
            }
        }
    }
    void move(QPoint & point);    /// \brief mvoes the tetromino by the QPoint
protected:
    QVector<QLabel*> squares;       /// \param squares represents every square in tetromino
    void squaresInit(QWidget * parent); /// \brief adds squares to QVector and sets it size
    QPoint pos;                         /// \param pos position of left top corner of matrix representing tetromino
    virtual std::array<std::array<bool, 3>, 3> g_matrix(); /// \brief returns matrix representing tetromino
    std::array<std::array<bool, 3>, 3> matrix = {{{{0, 0, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}}; /// \param matrix represents the shape of tetromino
};



class I: public Block
{
public:
    I(QWidget * parent, QPoint & position);
    I(QWidget * parent, QPoint position);
    //methods
    void display(); /// \brief adds graphics to tetromino
    //variables
    std::array<std::array<bool, 3>, 3> matrix = {{{{1, 1, 0}}, {{0, 1, 1}}, {{0, 0, 0}}}};  /// \param matrix represents the shape of tetromino
protected:
    std::array<std::array<bool, 3>, 3> g_matrix();          /// \brief returns matrix representing tetromino
};


#endif // BLOCK_H
