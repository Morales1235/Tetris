#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //setting the background image
    QPixmap background("./graphics/background.jpg");
    ui->backgroundLabel->setPixmap(background);

    for (int i = 0; i < floorMatrix.size(); i++)
        floorMatrix[i].fill(0);

    movingTimer = new QTimer(this);
    connect(movingTimer, SIGNAL(timeout()), this, SLOT(movingDown()));
    movingTimer->start(1200);

}

Widget::~Widget()
{
    delete ui;
}



void Widget::keyPressEvent(QKeyEvent * event)
{
        switch (event->key()) {
        case 0x41:      //key A
            if (!currentBlock->leftBorder() && possibleMove(0, -1)) currentBlock->move<int>(-blockSize.width(), 0);
            break;
        case 0x44:      //key D
            if (!currentBlock->rightBorder() && possibleMove(0, 1)) currentBlock->move<int>(blockSize.width(), 0);
            break;
        case 0x45:      //key E
            if (currentBlock->g_shape() != 4) { //! Fourth block is O, it should't be rotating in 5x5 matrix
                currentBlock->transponse();
                if (currentBlock->isAway() || !possibleMove(0, 0))
                {
                    currentBlock->transponse();
                    break;
                }
                if (currentBlock->g_shape() != 1)
                {
                    currentBlock->verticalReflection(); //! Don't know why I block is breaking every second rotate. Transponse is enough for that block
                    if (!possibleMove(0, 0)) currentBlock->verticalReflection();
                }
            }
            break;
        case 0x51:      //key Q
            if (currentBlock->g_shape() != 4) {
                currentBlock->transponse();
                if (currentBlock->isAway() || !possibleMove(0, 0))
                {
                    currentBlock->transponse();
                    break;
                }
                if (currentBlock->g_shape() != 1)
                {
                    currentBlock->horizontalReflection();
                    if (!possibleMove(0, 0)) currentBlock->horizontalReflection();
                }
            }
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

void Widget::movingDown()
{
    if (possibleMove(1, 0)) currentBlock->move(0, blockSize.height());
    else
    {
        addBlock();
        setCurrentBlock(new Block(this, startPoint, loss(1, 7)));
    }
}

void Widget::touchFloor()
{

}
/*
void Widget::initLayout()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            floorLayout->addWidget(new QLabel(ui->backgroundLabel), i, j);
        }
    }
}
*/

bool Widget::possibleMove(int di, int dj)
{
    bool temp = true;
    for (unsigned int i = 0; i < currentBlock->g_matrix().size(); i++)
    {
        for (unsigned int j = 0; j < currentBlock->g_matrix()[i].size(); j++)
        {
            if (currentBlock->g_matrix()[i][j] && floorMatrix[(currentBlock->g_pos().y() - 30)/blockSize.height() + i + 1 + di][(currentBlock->g_pos().x() - 10) / blockSize.width() + j + dj])
                temp = false;
                // adding to floor: floorMatrix[(block->g_pos().y() - 30)/blockSize.height() + i, (block->g_pos().x() - 10) / blockSize.width() + j] = 1;
        }
    }
    return temp;
}

void Widget::addBlock()
{
    for (unsigned int i = 0; i < currentBlock->g_matrix().size(); i++)
    {
        for (unsigned int j = 0; j < currentBlock->g_matrix()[i].size(); j++)
        {
            if (currentBlock->g_matrix()[i][j])
            {
                floorMatrix[(currentBlock->g_pos().y() - 30)/blockSize.height() + 1 + i][(currentBlock->g_pos().x() - 10) / blockSize.width() + j] = 1;
            }
        }
    }
}

void Widget::on_addButton_clicked()
{
    if (possibleMove(0, 0)) addBlock();
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << floorMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    setCurrentBlock(new Block(this, startPoint, loss(1, 7)));
}
