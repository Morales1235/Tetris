#ifndef WIDGET_H
#define WIDGET_H

//#include "matrix_transformations.cpp"
#include "block.h"
#include <QWidget>
#include <QKeyEvent>
#include <QTimer>

extern QPoint startPoint;
extern int loss(int min, int max);

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void keyPressEvent(QKeyEvent * event);
    void setCurrentBlock(Block * block); /// \brief sets which of blocks is current in the game

private slots:
    void on_pushButton_clicked();
    void movingDown();      /// \brief executing to move down tetromino
    void touchFloor();      /// \brief executen when block touches the floor
    bool possibleMove(int di, int dj);
    void addBlock();
    //void initLayout();

    void on_addButton_clicked();

private:
    Ui::Widget *ui;
    Block * currentBlock; /// \param currentBlock is Block which is in the game
    QTimer * movingTimer; /// \brief timer to moving down interval
    std::array<std::array<bool, 10>, 15> floorMatrix;   /// \param floorMatrix is matrix representing fallen tetrominos
    //QGridLayout * floorLayout;
};

#endif // WIDGET_H
