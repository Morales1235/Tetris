/**
  \brief    This is an abstract(not yet?) class representing one tetromino.
  **/

#ifndef TETROMINO_H
#define TETROMINO_H

#include <QLabel>
#include <QVector>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <unordered_map>

extern QSize blockSize;

typedef std::array<std::array<bool, 5>, 5> myMatrix;        //!Matrixes used to represent each tetromino
                                                            //!Which matrix must be the same, because of definition of objects... blah
                                                            //!They are 5x5 to fit all matrixes - biggest (I) has 4
                                                            //!But it also gives 3x3 tetrominos posibility to rotate around its middle square

class Tetromino
{
public:
    Tetromino();
    Tetromino(QWidget * parent, QPoint & position, int shapeNumber);
    Tetromino(const Tetromino &other);
    ~Tetromino();

    void move(int x, int y);    /// \brief mvoes the tetromino by the point
    void setPosition(QPoint &point);   /// \brief moves the tetromino to the point
    QPoint getPos();                     /// \return the position of tetromino
    myMatrix getMatrix(); /// \brief returns matrix representing tetromino
    void transponse();      /// \brief transposing the matrix of tetromino
    void horizontalReflection();        /// \brief Reflects the matrix by horizontal axis
    void verticalReflection();        /// \brief Reflects the matrix by vertical axis
    int getShapeNumber();                  /// \return the number of the shape(matrix)
    void removeSquares();                   /// \brief clean blocks in tetromino
    const QPixmap * getPixmap();                    /// \return the color of tetromino as pixmap

    Tetromino operator =(const Tetromino &other);            /// \brief assigment operator for block
    myMatrix operator = (const myMatrix & );    /// \brief change the matrix representing tetromino

protected:
    void squaresInit(QWidget * parent); /// \brief adds squares to QVector and sets it size

    QWidget * parent;
    myMatrix matrix = {{{{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}}}; /// \param matrix represents the shapeNumber of tetromino
    QPoint pos;                         /// \param pos position of left top corner of matrix representing tetromino
    int shapeNumber;              /// \param shapeNumber choosing which matrix represents shapeNumber
    int blocks = 4;                 /// \param blocks is number of blocks in tetromino
    QVector<std::shared_ptr<QLabel> > squares;       /// \param squares represents every square in tetromino


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



#endif // TETROMINO_H
