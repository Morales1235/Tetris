#ifndef WIDGET_H
#define WIDGET_H

//#include "matrix_transformations.cpp"
#include "block.h"
#include <QWidget>
#include <QKeyEvent>

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

private:
    Ui::Widget *ui;
    Block * currentBlock; /// \param currentBlock is Block which is in the game
};

#endif // WIDGET_H
