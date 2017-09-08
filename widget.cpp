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


    movingTimer = std::move(std::unique_ptr<QTimer> (new QTimer(this)));
    connect(movingTimer.get(), SIGNAL(timeout()), this, SLOT(movingDown()));

}

Widget::~Widget()
{
    delete ui;
}



void Widget::keyPressEvent(QKeyEvent * event)
{
        switch (event->key()) {
        case 0x41:      //key A
            if (isPossibleMove(0, -1)) currentBlock->move<int>(-blockSize.width(), 0);
            break;
        case 0x44:      //key D
            if (isPossibleMove(0, 1)) currentBlock->move<int>(blockSize.width(), 0);
            break;
        case 0x45:      //key E
            if (currentBlock->getShape() != 4) { //!Fourth block is O, it should't be rotating in 5x5 matrix
                currentBlock->transponse();
                if (!isPossibleMove(0, 0))
                {
                    currentBlock->transponse();
                    break;
                }
                if (currentBlock->getShape() != 1)
                {
                    currentBlock->verticalReflection(); //!Don't know why I block is breaking every second rotate. Transponse is enough for that block
                    if (!isPossibleMove(0, 0)) currentBlock->verticalReflection();
                }
            }
            break;
        case 0x51:      //key Q
            if (currentBlock->getShape() != 4) {
                currentBlock->transponse();
                if (!isPossibleMove(0, 0))
                {
                    currentBlock->transponse();
                    break;
                }
                if (currentBlock->getShape() != 1)
                {
                    currentBlock->horizontalReflection();
                    if (!isPossibleMove(0, 0)) currentBlock->horizontalReflection();
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
    currentBlock = std::move(tetrominos.last());
    currentBlock->setPosition(startPoint);
    nextBlock = std::move(std::shared_ptr<Block> (new Block(this, nextBlockPoint)));
    tetrominos.push_back(nextBlock);
    */
    ///Without qvector of tetrominos
    currentBlock = std::move(nextBlock);
    currentBlock->setPosition(startPoint);
    nextBlock = std::move(std::unique_ptr<Block> (new Block(this, nextBlockPoint, loss(1, 7))));
}

void Widget::on_pushButton_clicked()
{
    currentBlock->move<int>(0, 40);
}

void Widget::startGame()
{
    /*
    tetrominos.clear();
    nextBlock = std::move(std::shared_ptr<Block> (new Block(this, nextBlockPoint)));
    tetrominos.push_back(nextBlock);
    setCurrentBlock();
    movingTimer->start(moveInterval);
    */
    /////Without vector: tetrominos:
    nextBlock = std::move(std::unique_ptr<Block> (new Block(this, nextBlockPoint, loss(1, 7))));
    setCurrentBlock();
    movingTimer->start(*moveInterval);
}

void Widget::movingDown()
{
    if (isPossibleMove(1, 0)) currentBlock->move(0, blockSize.height());
    else if (currentBlock->getPos().y() == -10) gameOver();
    else
    {
        addBlock();
        setCurrentBlock();
    }
}

void Widget::touchFloor()
{

}


bool Widget::isPossibleMove(int di, int dj)
{
    bool check = true;
    int _i, _j;
    for (unsigned int i = 0; i < currentBlock->getMatrix().size(); i++)
    {
        for (unsigned int j = 0; j < currentBlock->getMatrix()[i].size(); j++)
        {
            _j = (currentBlock->getPos().x() - 10) / blockSize.width() + j + dj;
            _i = (currentBlock->getPos().y() - 30) / blockSize.height() + i + di + 1;
            if ((currentBlock->getMatrix()[i][j]) && (_i >= floorMatrix.size() || _j >= floorMatrix[_i].size() || _j < 0))   //!Checks if tetromino wants move outside the playground
            {
                check = false;
                break;
            }
            else if (currentBlock->getMatrix()[i][j] && floorMatrix[_i][_j])     //!Checks if tetromino will be on the other tetromino
            {
                check = false;
                break;
            }
        }
    }
    return check;
}

void Widget::addBlock()
{
    for (unsigned int i = 0; i < currentBlock->getMatrix().size(); i++)
    {
        for (unsigned int j = 0; j < currentBlock->getMatrix()[i].size(); j++)
        {
            if (currentBlock->getMatrix()[i][j])
            {
                floorMatrix[(currentBlock->getPos().y() - 30)/blockSize.height()+ i+ 1][(currentBlock->getPos().x() - 10) / blockSize.width() + j] = 1;
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
    if (isPossibleMove(0, 0)) addBlock();
    for (int i = 0; i < floorMatrix.size(); i++)
    {
        for (int j = 0; j < floorMatrix[i].size(); j++)
        {
            std::cout << floorMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    setCurrentBlock();
}

void Widget::on_startButton_clicked()
{
    startGame();
}
