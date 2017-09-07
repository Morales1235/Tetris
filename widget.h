#ifndef WIDGET_H
#define WIDGET_H

//#include "matrix_transformations.cpp"
#include "block.h"
#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <QDialogButtonBox>

extern QPoint startPoint;
extern QPoint nextBlockPoint;

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
    void setCurrentBlock(); /// \brief sets which of blocks is current in the game

private slots:
    void on_pushButton_clicked();
    void startGame();       /// \brief starts the game
    void movingDown();      /// \brief executing to move down tetromino
    void touchFloor();      /// \brief executen when block touches the floor
    bool possibleMove(int di, int dj);  /// \brief checks if is possible move on matrix by di dj
    void addBlock();                /// \brief adds current tetromino to matrix of floor
    void gameOver();                /// \brief execute when playground os full of blocks

    void on_addButton_clicked();

    void on_startButton_clicked();

private:
    Ui::Widget *ui;
    std::shared_ptr<Block> currentBlock; /// \param currentBlock a block currently in playground
    std::shared_ptr<Block> nextBlock;   /// \param nextBlock pointer to block displaying as next Block
    QTimer * movingTimer; /// \brief timer to moving down interval
    std::array<std::array<bool, 10>, 15> floorMatrix;   /// \param floorMatrix is matrix representing fallen tetrominos
    int moveInterval;                                   /// \param moveInterval interval of moving down
    QVector<std::shared_ptr<Block> > tetrominos;
};

#endif // WIDGET_H
