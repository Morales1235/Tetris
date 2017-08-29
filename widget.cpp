#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //setting the background image
    QPixmap background("./graphics/background.jpg");
    ui->backgroundLabel->setPixmap(background.scaled(ui->backgroundLabel->size(), Qt::KeepAspectRatio));

    currentBlock = new Block();

}

Widget::~Widget()
{
    delete ui;
    //delete currentBlock;
}
void Widget::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case 0x41:
        currentBlock->move<int>(-40, 0);
        break;
    case 0x44:
        currentBlock->move<int>(40, 0);
        break;
    default:
        break;
    }
}

void Widget::setCurrentBlock(Block * block)
{
    currentBlock = block;
}

void Widget::on_pushButton_clicked()
{
    currentBlock->move<int>(0, 40);
}
