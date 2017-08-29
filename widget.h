#ifndef WIDGET_H
#define WIDGET_H

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
    void setCurrentBlock(Block * block);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    Block * currentBlock;
};

#endif // WIDGET_H
