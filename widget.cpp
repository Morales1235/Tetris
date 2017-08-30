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


}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case 0x41:      //key A
        currentBlock->move<int>(-40, 0);
        break;
    case 0x44:      //key D
        currentBlock->move<int>(40, 0);
        break;
    case 0x51:      //key Q
        currentBlock->transponse();
        currentBlock->horizontalReflection();
        currentBlock->move(0,0);
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
