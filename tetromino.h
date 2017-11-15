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
#include "shapes.h"
//#include <unordered_map>

extern QSize blockSize;

class Tetromino
{
public:
    Tetromino();
    Tetromino(QWidget * parent, QPoint & position);
    Tetromino(const Tetromino &other);
    ~Tetromino();

    void move(int x, int y);    /// \brief mvoes the tetromino by the point
    void setPosition(QPoint &point);   /// \brief moves the tetromino to the point
    QPoint getPosAtMatrix();                     /// \return the position of tetromino
    myMatrix getMatrix(); /// \brief returns matrix representing tetromino
    void transponse();      /// \brief transposing the matrix of tetromino
    void horizontalReflection();        /// \brief Reflects the matrix by horizontal axis
    void verticalReflection();        /// \brief Reflects the matrix by vertical axis
    int getShapeNumber();                  /// \return the number of the shape(matrix)
    const QPixmap * getPixmap();                    /// \return the color of tetromino as pixmap

    Tetromino operator = (const Tetromino &other);            /// \brief assigment operator for block
    myMatrix operator = (const myMatrix & );    /// \brief change the matrix representing tetromino

protected:
    void squaresInit(QWidget * parent); /// \brief adds squares to QVector and sets it size

    QWidget * parent;
    myMatrix matrix = {{{{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}, {{0, 0, 0, 0, 0}}}}; /// \param matrix represents the shapeNumber of tetromino
    QPoint pos;                         /// \param pos position of left top corner of matrix representing tetromino
    Shapes * shapes;                    /// \param stores matrixes and colors for blocks
    int shapeNumber;              /// \param shapeNumber choosing which matrix represents shapeNumber
    QVector<std::shared_ptr<QLabel> > squares;       /// \param squares represents every square in tetromino


};



#endif // TETROMINO_H
