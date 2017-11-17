#ifndef SHAPES_H
#define SHAPES_H
#include <array>
#include <memory>
#include <QPixmap>
#include <QVector>

typedef std::array<std::array<bool, 5>, 5> myMatrix;        //!Matrixes used to represent each tetromino
                                                            //!Which matrix must be the same, because of definition of objects... blah
                                                            //!They are 5x5 to fit all matrixes - biggest (I) has 4
                                                            //!But it also gives 3x3 tetrominos posibility to rotate around its middle square

extern QSize blockSize;

class Shapes
{
public:
    static Shapes * getInstance();  /// \brief "constructor" of singleton
    myMatrix getMatrix(int);        /// \return myMatrix depending on argument passed in
    QPixmap getPixmap(int);         /// \return QPixmap depending on argument passed in
private:
    Shapes();
    Shapes(Shapes const &);
    void operator = (Shapes const &);
    static Shapes * instance;           /// \param instance instance of singleton

    std::vector <myMatrix> matrixes;    /// \param matrixes stores all 7 matrixes
    QVector <QPixmap> pixmaps;          /// \param pixmap sotres all 7 pixmaps

    ///Matrixes representing shapes
    ///
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

enum shapeNumbers
{
    LIGHT_BLUE,
    DARK_BLUE,
    ORANGE,
    YELLOW,
    GREEN,
    PURPLE,
    RED
};

#endif // SHAPES_H
