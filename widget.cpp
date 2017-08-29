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
    if (event->key() == Qt::Key_Right) ;
}

void Widget::setCurrentBlock(Block * block)
{
    currentBlock = block;
}

void Widget::on_pushButton_clicked()
{
    currentBlock->move(0, 40);
}
