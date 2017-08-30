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
    case 0x45:      //key E
        if (currentBlock->g_shape() != 4) { //! Fourth block is O, it should't be rotating in 5x5 matrix
        currentBlock->transponse();
        if (currentBlock->g_shape() != 1) currentBlock->verticalReflection(); //! Don't know why I block is breaking every second rotate. Transponse is enough for that block
        currentBlock->move(0, 0);}
        break;
    case 0x51:      //key Q
        if (currentBlock->g_shape() != 4) {
        currentBlock->transponse();
        if (currentBlock->g_shape() != 1) currentBlock->horizontalReflection();
        currentBlock->move(0,0);}
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
