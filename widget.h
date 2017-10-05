#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QInputDialog>
#include <QMenuBar>
#include <QTextStream>
#include <QFile>
#include <QMultiMap>
#include <QDebug>
#include "highscoreddialog.h"
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

private slots:
    void startGame();       /// \brief starts the game
    void setInitValues();   /// \brief sets values as timer, score to initial
    void setPlayerName();   /// \brief sets the name of player
    void setNextTetromino();    /// \brief sets which tetromino will be next in game
    bool isPossibleMove(int di, int dj);  /// \brief checks if is possible move on matrix by di dj
    void rotateRight();         /// \brief rotates current tetroimno right
    void rotateLeft();          /// \brief rotates current tetroimno left
    void movingDownLogic();      /// \brief executing to move down tetromino
    void setCurrentTetromino(); /// \brief sets which of tetrominos is current in the game
    void moveTetrominoDown();   /// \brief moves current tetromino down
    void hardDrop();        /// \brief tetromino fall to the floor
    void addTetrominoToFloor();                /// \brief adds current tetromino to matrix of floor
    void removeFullRows(); /// \brief checks if any row is filled
    void addPointToScore();                /// \brief add one point to score
    void gameOver();                    /// \brief executed when game ends - tetrominos are on top
    void saveScore();                   /// \brief saves the score to highscore file
    pHighscores readHighscores();                   /// \brief read high scores from file

    void on_startButton_clicked();

    void on_highscoresButton_clicked();

    void on_exitButton_clicked();

    void on_pushButton_clicked();

signals:


private:
    Ui::Widget *ui;
    std::unique_ptr<Tetromino> currentTetromino = nullptr; /// \param currentTetromino a tetromino currently in playground
    std::unique_ptr<Tetromino> nextTetromino = nullptr;   /// \param nextTetromino pointer to tetromino displaying as next tetromino
    std::unique_ptr<QTimer> movingTimer; /// \brief timer to moving down interval
    //std::array<std::array<bool, 10>, 15> floorMatrix;   /// \param floorMatrix is matrix representing fallen tetrominos
    int moveInterval;    /// \param moveInterval interval of moving down
    std::unique_ptr<Floor> myFloor = std::unique_ptr<Floor>(new Floor(this));
    std::unique_ptr<QString> playerName;     /// \param playerName name of the player
    unsigned int score;    /// \param score how much points the player gained
    QFile * scoresFile; /// \file to save scores
};

#endif // WIDGET_H
