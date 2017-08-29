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
    void setPos(QPoint & leftTop);
    std::array<std::array<bool, 3>, 3> matrix = {{{{0, 0, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}};
protected:
    QVector<QLabel*> squares;
    void squaresInit(QWidget * parent);
    QPoint pos;
    //bool matrix[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    virtual std::array<std::array<bool, 3>, 3> g_matrix();
private:
};



class I: public Block
{
public:
    I(QWidget * parent, QPoint & position);
    I(QWidget * parent, QPoint position);
    //methods
    void display();
    //variables
protected:
    std::array<std::array<bool, 3>, 3> g_matrix();
private:
    std::array<std::array<bool, 3>, 3> matrix = {{{{1, 1, 0}}, {{0, 1, 1}}, {{0, 0, 0}}}};
};


#endif // BLOCK_H
