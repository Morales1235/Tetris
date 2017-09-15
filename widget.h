#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <QDialogButtonBox>
#include "tetromino.h"
#include "floor.h"

extern QPoint startPoint;
extern QPoint nextPoint;
extern int loss(int, int);

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
    void keyReleaseEvent(QKeyEvent * event);
    void setCurrentTetromino(); /// \brief sets which of tetrominos is current in the game

    /*
    std::unordered_map<std::string, QPixmap> colors = {
            { "lightBlue",  QPixmap("./graphics/light_blue.jpg") },
            { "darkBlue",   QPixmap("./graphics/dark_blue.jpg") },
            { "orange",     QPixmap("./graphics/orange.jpg") },
            { "yellow",     QPixmap("./graphics/yellow.jpg") },
            { "green",      QPixmap("./graphics/green.jpg") },
            { "purple",     QPixmap("./graphics/purple.jpg") },
            { "red",        QPixmap("./graphics/red.jpg") }
        };
    */

private slots:
    void setNextTetromino();    /// \brief sets which tetromino will be next in game
    void rotateRight();         /// \brief rotates current tetroimno right
    void rotateLeft();          /// \brief rotates current tetroimno left
    void startGame();       /// \brief starts the game
    void movingDownLogic();      /// \brief executing to move down tetromino
    void moveTetrominoDown();   /// \brief moves current tetromino down
    void hardDrop();        /// \brief tetromino fall to the floor
    void removeFullRows(); /// \brief checks if any row is filled
    bool isPossibleMove(int di, int dj);  /// \brief checks if is possible move on matrix by di dj
    void addTetrominoToFloor();                /// \brief adds current tetromino to matrix of floor
    void gameOver();                /// \brief execute when playground os full of tetrominos
    void addPointToScore();                /// \brief add one point to score

    void on_startButton_clicked();

    void on_matrixButton_clicked();

private:
    Ui::Widget *ui;
    std::unique_ptr<Tetromino> currentTetromino = nullptr; /// \param currentTetromino a tetromino currently in playground
    std::unique_ptr<Tetromino> nextTetromino = nullptr;   /// \param nextTetromino pointer to tetromino displaying as next tetromino
    std::unique_ptr<QTimer> movingTimer; /// \brief timer to moving down interval
    //std::array<std::array<bool, 10>, 15> floorMatrix;   /// \param floorMatrix is matrix representing fallen tetrominos
    int moveInterval;    /// \param moveInterval interval of moving down
    std::unique_ptr<Floor> myFloor = std::unique_ptr<Floor>(new Floor(this));
    unsigned int score;    /// \param score how much points the player gained
};

#endif // WIDGET_H
