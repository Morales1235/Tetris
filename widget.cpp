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

    //tetrominos = new QVector<std::shared_ptr<Block> > (30);
    tetrominos = new QVector<Block *> (30);

    moveInterval = 1200;
    movingTimer = new QTimer(this);
    connect(movingTimer, SIGNAL(timeout()), this, SLOT(movingDown()));

}

Widget::~Widget()
{
    delete ui;
}



void Widget::keyPressEvent(QKeyEvent * event)
{
        switch (event->key()) {
        case 0x41:      //key A
            if (possibleMove(0, -1)) currentBlock->move<int>(-blockSize.width(), 0);
            break;
        case 0x44:      //key D
            if (possibleMove(0, 1)) currentBlock->move<int>(blockSize.width(), 0);
            break;
        case 0x45:      //key E
            if (currentBlock->g_shape() != 4) { //!Fourth block is O, it should't be rotating in 5x5 matrix
                currentBlock->transponse();
                if (currentBlock->isAway() || !possibleMove(0, 0))
                {
                    currentBlock->transponse();
                    break;
                }
                if (currentBlock->g_shape() != 1)
                {
                    currentBlock->verticalReflection(); //!Don't know why I block is breaking every second rotate. Transponse is enough for that block
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

void Widget::setCurrentBlock()
{
    /*
    currentBlock = std::move(tetrominos->last());
    currentBlock->setPosition(startPoint);
    nextBlock = std::move(std::shared_ptr<Block> (new Block(this, nextBlockPoint)));  //new Block(this, nextBlockPoint);
    tetrominos->push_back(nextBlock);
    */


    currentBlock = tetrominos->last();
    currentBlock->setPosition(startPoint);
    nextBlock = new Block(this, nextBlockPoint);
    tetrominos->push_back(nextBlock);

}

void Widget::on_pushButton_clicked()
{
    currentBlock->move<int>(0, 40);
}

void Widget::startGame()
{
    /*
    tetrominos->clear();
    nextBlock = std::move(std::shared_ptr<Block> (new Block(this, nextBlockPoint)));    //new Block(this, nextBlockPoint);
    tetrominos->push_back(nextBlock);
    setCurrentBlock();
    movingTimer->start(moveInterval);
    */

    if (!firstGame)
    {
        for (int i = 0; i < tetrominos->size(); i++)
        {
            tetrominos->at(i)->removeSquares();
        }
    }

    firstGame = false;

    tetrominos->clear();
    nextBlock= new Block(this, nextBlockPoint);
    tetrominos->push_back(nextBlock);
    setCurrentBlock();
    movingTimer->start(moveInterval);

}

void Widget::movingDown()
{
    if (possibleMove(1, 0)) currentBlock->move(0, blockSize.height());
    else if (currentBlock->g_pos().y() == -10) gameOver();
    else
    {
        addBlock();
        setCurrentBlock();
    }
}

void Widget::touchFloor()
{

}


bool Widget::possibleMove(int di, int dj)
{
    int _i, _j;
    bool temp = true;
    for (unsigned int i = 0; i < currentBlock->g_matrix().size(); i++)
    {
        for (unsigned int j = 0; j < currentBlock->g_matrix()[i].size(); j++)
        {
            _j = (currentBlock->g_pos().x() - 10) / blockSize.width() + j + dj;
            _i = (currentBlock->g_pos().y() - 30) / blockSize.height() + i + di + 1;
            std::cout << "Checking for: " << _i << ", " << _j << std::endl;
            if ((currentBlock->g_matrix()[i][j]) && (_i >= floorMatrix.size() || _j >= floorMatrix[_i].size() || _j < 0))   //!Checks if tetromino wants move outside the playground
            {
                temp = false;
                std::cout << "set false for: " << _i << ", " << _j << std::endl;
                //break;
            }
            else if (currentBlock->g_matrix()[i][j] && floorMatrix[_i][_j])     //!Checks if tetromino will be on the other tetromino
                temp = false;
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
                floorMatrix[(currentBlock->g_pos().y() - 30)/blockSize.height()+ i+ 1][(currentBlock->g_pos().x() - 10) / blockSize.width() + j] = 1;
            }
        }
    }
}

void Widget::gameOver()
{
    movingTimer->stop();
    QMessageBox::information(this, "Game over", "You finished the game with: ", QDialogButtonBox::Close);
}

void Widget::on_addButton_clicked()
{
    if (possibleMove(0, 0)) addBlock();
    for (int i = 0; i < floorMatrix.size(); i++)
    {
        for (int j = 0; j < floorMatrix[i].size(); j++)
        {
            std::cout << floorMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    setCurrentBlock();
}

void Widget::on_startButton_clicked()
{
    startGame();
}
